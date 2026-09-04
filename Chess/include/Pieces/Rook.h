#ifndef ROOK_H
#define ROOK_H

#include "Pieces/Piece.h"

class Rook : public Piece {
    public:
        Rook(bool isWhite); // constructor
        virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override; // check if the movement is valid
        virtual std::unique_ptr<Piece> clone() const override { return std::make_unique<Rook>(*this); } // for cloning the piece
    };
#endif // ROOK_H
