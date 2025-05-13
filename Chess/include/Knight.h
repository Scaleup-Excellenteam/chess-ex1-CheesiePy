#ifndef KINGHT_H
#define KINGHT_H

#include "Piece.h"


class Knight : public Piece {
public:
    Knight(bool isWhite); // constructor
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override; // check if the movement is valid
};



#endif // KINGHT_H