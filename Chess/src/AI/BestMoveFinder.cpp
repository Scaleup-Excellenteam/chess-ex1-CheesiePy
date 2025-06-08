#include "AI/BestMoveFinder.h"


#include <algorithm>   // std::stable_sort
#include <cctype>      // std::tolower
#include <climits>     // INT_MIN

/*  All symbols are defined inside namespace AI
 *  --------------------------------------------------------------*/
namespace AI
{

/* --------------------------------------------------------------------------
 *  Helper: convert a piece symbol to a crude material score
 * --------------------------------------------------------------------------*/
int BestMoveFinder::pieceValue(char symbol)
{
    switch (std::tolower(static_cast<unsigned char>(symbol)))
    {
        case 'p': return 1;   // pawn
        case 'n':             // knight
        case 'b': return 3;   // bishop
        case 'r': return 5;   // rook
        case 'q': return 9;   // queen
        default : return 0;   // king or empty square
    }
}

/* --------------------------------------------------------------------------
 *  Evaluate a single move (captures only, depth-0)
 * --------------------------------------------------------------------------*/
int BestMoveFinder::evaluateMove(const Board& board,
                                 const CMove& move) const
{
    const Piece* src = board.getPiece(move.srcRow,  move.srcCol);
    const Piece* dst = board.getPiece(move.destRow, move.destCol);

    if (!src || !dst || dst->getIsWhite() == src->getIsWhite())
        return 0;                               // empty square or own piece

    return pieceValue(dst->getSymbol());        // genuine capture
}
/* --------------------------------------------------------------------------
 *  Return the *single* best move for the side to play
 * --------------------------------------------------------------------------*/
MoveScorePair BestMoveFinder::findBestMove(const Board& board,
                                           bool          isWhite) const
{
    MoveScorePair best{ CMove{}, INT_MIN };      // default “no-move” sentinel

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            const Piece* piece = board.getPiece(row, col);
            if (!piece || piece->getIsWhite() != isWhite)
                continue;                         // empty or opponent piece

            for (const CMove& mv : piece->legalMoves(row, col, board))
            {
                int score = evaluateMove(board, mv);
                if (score > best.score)          // strictly better only
                    best = { mv, score };
            }
        }
    }
    return best;
}

/* --------------------------------------------------------------------------
 *  Collect and rank the top-N moves (used by Chess.cpp)
 * --------------------------------------------------------------------------*/
std::vector<MoveScorePair>
findBestMoves(const Board& board, bool isWhite, int limit)
{
    std::vector<MoveScorePair> candidates;
    candidates.reserve(128);                     // avoid reallocs

    BestMoveFinder finder;                       // stateless helper

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            const Piece* piece = board.getPiece(row, col);
            if (!piece || piece->getIsWhite() != isWhite)
                continue;

            for (const CMove& mv : piece->legalMoves(row, col, board))
            {
                int score = finder.evaluateMove(board, mv);
                candidates.push_back({ mv, score });
            }
        }
    }

    /* Sort best-score first; stable_sort keeps deterministic ordering
       for moves with identical scores. */
    std::stable_sort(candidates.begin(), candidates.end(),
                     [](const MoveScorePair& a, const MoveScorePair& b)
                     {
                         return a.score > b.score;
                     });

    if (limit > 0 && static_cast<int>(candidates.size()) > limit)
        candidates.resize(limit);

    return candidates;
}

} // namespace AI
