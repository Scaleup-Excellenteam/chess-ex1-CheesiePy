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
            // --- CORRECTED FORMATTING LOGIC ---
            // Column (0-7) becomes file ('a'-'h')
            char fileChar = 'a' + col;
            // Row (0-7) becomes rank ('8'-'1')
            char rankChar = '1' + (7 - row);
            // --- END CORRECTION ---
            return {fileChar, rankChar};
        };
        return sq(move.srcRow, move.srcCol) +
               sq(move.destRow, move.destCol) +
               " (+" + std::to_string(score) + ")";
    }
};

/* ostream helper */
inline std::ostream& operator<<(std::ostream& os,
                                const MoveScorePair& p)
{
    return os << p.toString();
}
