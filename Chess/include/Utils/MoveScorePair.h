#pragma once
#include <string>
#include "Utils/CMove.h"

/* ------------------------------------------------------------------------
 *  A move + its score, with printable helper
 *  Board coordinates: letter=ROW (A-H), digit=COL (1-8)
 * ----------------------------------------------------------------------*/
struct MoveScorePair
{
    CMove move;
    int   score{0};

    std::string toString() const
    {
        auto sq = [](int row, int col) -> std::string
        {
            char rowLetter = 'A' + row;   // 0→A
            char colDigit  = '1' + col;   // 0→1
            return {rowLetter, colDigit};
        };
        return sq(move.srcRow,move.srcCol) +
               sq(move.destRow,move.destCol) +
               " (+" + std::to_string(score) + ")";
    }
};

/* ostream helper */
inline std::ostream& operator<<(std::ostream& os,
                                const MoveScorePair& p)
{
    return os << p.toString();
}
