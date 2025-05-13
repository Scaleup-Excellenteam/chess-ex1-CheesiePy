#include "AI/BestMoveFinder.h"
using namespace AI;

// comparator: highest‐score first
struct RecMoveCmp {
    int operator()(RecommendedMove const &a,
                   RecommendedMove const &b) const {
        return a.score - b.score;
    }
};

// helper to flip side
inline bool opponent(bool white) { return !white; }

static int staticEval(const Board& b, bool white) {
    // your depth‐0 evaluation: captures, threats, etc.
    // return +ve if good for 'white', -ve if good for 'black'.
    // (if evaluating for black, you could return -staticEval(b,true))
    // … fill this in …
    return 0;
}

// minimax with no alpha‐beta
static int minimax(const Board& board,
                   bool origWhite,
                   bool curWhite,
                   int depth)
{
    if (depth == 0) {
        return staticEval(board, origWhite);
    }

    auto moves = board.generateLegalMoves(curWhite);
    if (moves.empty()) {
        // checkmate vs stalemate: you need board.inCheck(curWhite)
        return board.inCheck(curWhite)
               ? (curWhite == origWhite ? -10000 : +10000)
               : 0;
    }

    if (curWhite == origWhite) {
        // MAX node
        int best = -100000;
        for (auto const &mv : moves) {
            Board nb = board;
            nb.applyMove(mv);
            best = std::max(best,
                            minimax(nb, origWhite,
                                    opponent(curWhite),
                                    depth - 1));
        }
        return best;
    } else {
        // MIN node
        int best = +100000;
        for (auto const &mv : moves) {
            Board nb = board;
            nb.applyMove(mv);
            best = std::min(best,
                            minimax(nb, origWhite,
                                    opponent(curWhite),
                                    depth - 1));
        }
        return best;
    }
}

std::vector<RecommendedMove>
findBestMoves(const Board& board,
              bool whiteToMove,
              int maxDepth)
{
    PriorityQueue<RecommendedMove,RecMoveCmp> pq;

    // step 1: generate every legal move for side to move
    for (auto const &mv : board.generateLegalMoves(whiteToMove)) {
        Board nb = board;
        nb.applyMove(mv);
        // step 2: score = minimax at depth-1 (since we already made 1 ply)
        int score = minimax(nb,
                            whiteToMove,      // original perspective
                            opponent(whiteToMove), // now opponent to move
                            maxDepth - 1);

        pq.push(RecommendedMove{mv, score});
        if (pq.size() > 5) pq.poll();  // keep only top 5
    }

    // extract in descending order
    std::vector<RecommendedMove> out;
    while (!pq.empty()) out.push_back(pq.poll());
    return out;
}
