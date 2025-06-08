#ifndef AI_BEST_MOVE_FINDER_H
#define AI_BEST_MOVE_FINDER_H
/**
 * @file BestMoveFinder.h
 * @brief A simple material-only evaluator that can pick either
 *        a single best move or a short list of the top-N moves.
 *
 *  ✔  Stateless, re-entrant, unit-test friendly
 *  ✔  Easy to swap in a deeper search later
 */

#include <vector>
#include <climits>          // INT_MIN

#include "Board.h"
#include "../Utils/CMove.h"
#include "../Utils/MoveScorePair.h"   // struct MoveScorePair { CMove move; int score; }

namespace AI
{
    /*----------------------------------------------------------------------
     * Bring the global POD into this namespace so declarations and
     * definitions agree on exactly the same type.
     *--------------------------------------------------------------------*/
    using ::MoveScorePair;

    class BestMoveFinder
    {
    public:
        BestMoveFinder() = default;                    // trivial ctor

        /** Return the single best move for the side to play. */
        MoveScorePair findBestMove(const Board& board,
                                   bool isWhite) const;

        /** Evaluate one move by the material it would capture (+score). */
        int evaluateMove(const Board& board,
                         const CMove& move) const;

    private:
        /** Helper: convert piece symbol to a crude material value. */
        static int pieceValue(char symbol);
    };

    /*----------------------------------------------------------------------
     * Helper used by Chess.cpp: return up to @p limit moves, sorted
     * best-first.  Pass limit == 0 to get *all* ranked moves.
     *--------------------------------------------------------------------*/
    std::vector<MoveScorePair>
    findBestMoves(const Board& board, bool isWhite, int limit);

} // namespace AI

#endif // AI_BEST_MOVE_FINDER_H
