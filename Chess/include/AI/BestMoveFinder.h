#ifndef AI_BESTMOVEFINDER_H
#define AI_BESTMOVEFINDER_H
#include <vector>
#include "../Board.h"           // your Board API
#include "../Utils/PriorityQueue.h"

namespace AI {

struct RecommendedMove {
    CMove m;             // the move (defined in Board.h)
    int score;           // higher = better

        // new helper
    std::string toString() const {
        std::string s;
        s += char('a' + m.srcCol);
        s += char('1' + m.srcRow);
        s += char('a' + m.destCol);
        s += char('1' + m.destRow);
        s += " (score " + std::to_string(score) + ")";
        return s;
    }
};

// / Finds up to 5 best moves for the side to move.
// / @param board         current position
// / @param whiteToMove   true = white’s turn; false = black’s turn
// / @param maxDepth      how many plies to look ahead (default = 2)
std::vector<RecommendedMove>
findBestMoves(const Board& board,
              bool whiteToMove,
              int maxDepth = 2);

} // namespace AI

#endif //AI_BESTMOVEFINDER_H