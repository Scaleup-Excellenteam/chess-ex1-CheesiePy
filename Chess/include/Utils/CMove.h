#ifndef CMOVE_H
#define CMOVE_H

struct CMove
{
    int srcRow  {0};
    int srcCol  {0};
    int destRow {0};
    int destCol {0};

    /* Convenience ctor */
    constexpr CMove(int sR = 0, int sC = 0, int dR = 0, int dC = 0) noexcept
        : srcRow(sR), srcCol(sC), destRow(dR), destCol(dC) {}

    
};

#endif  // UTILS_CMOVE_H
