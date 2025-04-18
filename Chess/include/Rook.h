#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
    public:
        Rook(bool isWhite); // constructor
        virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override; // check if the movement is valid
    };
#endif // ROOK_H
