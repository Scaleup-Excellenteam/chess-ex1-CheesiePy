#include "AI/BestMoveFinder.h"
#include "Board.h"
#include <algorithm>      // max, min, stable_sort
#include <cctype>         // tolower, islower
#include <climits>        // INT_MIN
#include <limits>
#include <vector>
#include "Utils/ThreadPoolSingleton.h"   // globalPool()
#include "Utils/SafeMovePQ.h"
// ──────────────────────────────────────────────────────────────────────────
// Helpers
// ──────────────────────────────────────────────────────────────────────────
static inline bool isWhitePiece(const Piece* p)
{
    return p && std::islower(static_cast<unsigned char>(p->getSymbol()));
}

static std::vector<CMove> genMoves(const Board& b, bool wantWhite)
{
    std::vector<CMove> out;
    out.reserve(128);

    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
        {
            const Piece* pc = b.getPiece(r, c);
            if (!pc || isWhitePiece(pc) != wantWhite)
                continue;

            for (const CMove& mv : pc->legalMoves(r, c, b))
                out.push_back(mv);
        }
    return out;
}

// ──────────────────────────────────────────────────────────────────────────
// namespace AI
// ──────────────────────────────────────────────────────────────────────────
namespace AI
{

// piece values ───────────────────────────────────────────────────────────
int BestMoveFinder::pieceValue(char s)
{
    switch (std::tolower(static_cast<unsigned char>(s)))
    {
        case 'p': return 1;
        case 'n':
        case 'b': return 3;
        case 'r': return 5;
        case 'q': return 9;
        default : return 0;
    }
}

// capture-only quick eval (still used by old GUI traces) ─────────────────
int BestMoveFinder::evaluateMove(const Board& b, const CMove& m) const
{
    const Piece* src = b.getPiece(m.srcRow,  m.srcCol);
    const Piece* dst = b.getPiece(m.destRow, m.destCol);

    if (!src || !dst || isWhitePiece(src) == isWhitePiece(dst))
        return 0;
    return pieceValue(dst->getSymbol());
}

// static material eval ───────────────────────────────────────────────────
int BestMoveFinder::evaluateBoard(const Board& b)
{
    int sum = 0;
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
        {
            const Piece* p = b.getPiece(r, c);
            if (!p) continue;
            int v = pieceValue(p->getSymbol());
            sum  += isWhitePiece(p) ?  v : -v;
        }
    return sum;
}

// ─────────────────────────────────────────────────────────────────────────
// Minimax + αβ  (NO board copies – uses apply / undo)
// ─────────────────────────────────────────────────────────────────────────
int BestMoveFinder::minimax(Board& board,
                            int depth,
                            int alpha,
                            int beta,
                            bool sideToMove /*true = white*/)
{
    if (depth == 0)
        return evaluateBoard(board);

    auto moves = genMoves(board, sideToMove);
    if (moves.empty())
        return evaluateBoard(board);          // stalemate / mate

    if (sideToMove)   // white (maximiser)
    {
        int best = std::numeric_limits<int>::min();
        for (const CMove& mv : moves)
        {
            const Piece* dst = board.getPiece(mv.destRow, mv.destCol);
            if (dst && isWhitePiece(dst))      // self-capture
                continue;

            board.applyMove(mv);
            int val = minimax(board, depth - 1, alpha, beta, false);
            board.undoMove(mv);

            best  = std::max(best, val);
            alpha = std::max(alpha, val);
            if (beta <= alpha) break;          // β-cutoff
        }
        return best;
    }
    else              // black (minimiser)
    {
        int best = std::numeric_limits<int>::max();
        for (const CMove& mv : moves)
        {
            const Piece* dst = board.getPiece(mv.destRow, mv.destCol);
            if (dst && !isWhitePiece(dst))
                continue;

            board.applyMove(mv);
            int val = minimax(board, depth - 1, alpha, beta, true);
            board.undoMove(mv);

            best  = std::min(best, val);
            beta  = std::min(beta, val);
            if (beta <= alpha) break;          // α-cutoff
        }
        return best;
    }
}

// ─────────────────────────────────────────────────────────────────────────
// Root search helpers (hints / single best move)
// ─────────────────────────────────────────────────────────────────────────
MoveScorePair BestMoveFinder::findBestMove(const Board& board,
                                           bool isWhite) const
{
    Board root = board;                        // one deep copy, kept intact
    MoveScorePair best{ CMove{}, std::numeric_limits<int>::min() };

    for (const CMove& mv : genMoves(root, isWhite))
    {
        const Piece* dst = root.getPiece(mv.destRow, mv.destCol);
        if (dst && isWhitePiece(dst) == isWhite)   // own piece
            continue;

        root.applyMove(mv);
        int score = minimax(root,
                            DEFAULT_DEPTH - 1,
                            std::numeric_limits<int>::min(),
                            std::numeric_limits<int>::max(),
                            !isWhite);
        root.undoMove(mv);

        if (score > best.score)
            best = { mv, score };
    }
    return best;
}

std::vector<MoveScorePair>
findBestMoves(const Board& board, bool isWhite, int limit)
{
    /* 1. fully-legal root moves from Board */
    std::vector<CMove> all = board.generateLegalMoves(isWhite);

    /* ——— NEW ——— filter out moves whose source piece is the wrong colour */
    std::vector<CMove> rootMoves;
    rootMoves.reserve(all.size());
    for (const CMove& mv : all)
    {
        const Piece* src = board.getPiece(mv.srcRow, mv.srcCol);
        if (src && isWhitePiece(src) == isWhite)          // keep only true side
            rootMoves.push_back(mv);
    }
    if (rootMoves.empty()) return {};
    /* ——— END NEW ——— */

    /* 2. bucket by source square (≤64 buckets) */
    std::array<std::vector<CMove>, 64> buckets;
    for (const CMove& mv : rootMoves)
        buckets[mv.srcRow * 8 + mv.srcCol].push_back(mv);

    /* 3. parallel scoring on the global pool */
    SafeMovePQ pq;
    std::vector<std::future<void>> futs;

    for (const auto& bucket : buckets)
    {
        if (bucket.empty()) continue;

        futs.emplace_back(
            globalPool().enqueue([&, bucket] {
                Board local = board;
                BestMoveFinder finder;


                for (const CMove& mv : bucket)
                {
                    const Piece* dst = local.getPiece(mv.destRow, mv.destCol);
                    if (dst && (symIsWhite(dst->getSymbol()) == isWhite))  // own piece
                        continue;  // skip self-captures
                    local.applyMove(mv);
                    int score = finder.minimax(local,
                                               BestMoveFinder::DEFAULT_DEPTH - 1,
                                               std::numeric_limits<int>::min(),
                                               std::numeric_limits<int>::max(),
                                               !isWhite);
                    local.undoMove(mv);

                    pq.push({ mv, score });
                }
            })
        );
    }

    for (auto& f : futs) f.get();                 // 4. wait workers

    std::vector<MoveScorePair> out;               // 5. pop best K
    out.reserve(limit > 0 ? limit : rootMoves.size());
    while ((limit <= 0 || static_cast<int>(out.size()) < limit))
    {
        auto best = pq.try_pop();
        if (!best) break;
        out.push_back(*best);
    }
    return out;
}

} // namespace AI
