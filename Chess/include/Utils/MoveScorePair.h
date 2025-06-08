#pragma once
#include <string>
#include "Utils/CMove.h"

/* ------------------------------------------------------------------------
 *  A move + its score, with printable helper
 *  Our board uses:   letter = ROW  (A-H, top→bottom)
 *                    digit  = COL  (1-8, left→right)
 * ----------------------------------------------------------------------*/
struct MoveScorePair
{
    CMove move;
    int   score{0};

    std::string toString() const
    {
        auto sq = [](int row, int col) -> std::string
        {
            char rowLetter = 'A' + row;   // 0 → 'A', 1 → 'B', ...
            char colDigit  = '1' + col;   // 0 → '1', 1 → '2', ...
            return {rowLetter, colDigit};
        };

        return sq(move.srcRow,  move.srcCol) +
               sq(move.destRow, move.destCol) +
               " (+" + std::to_string(score) + ")";
    }
};

/* Nice C++-stream helper */
inline std::ostream& operator<<(std::ostream& os, const MoveScorePair& p)
{
    return os << p.toString();
}
