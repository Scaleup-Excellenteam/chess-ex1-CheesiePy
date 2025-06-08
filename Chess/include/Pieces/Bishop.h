#ifndef BISHOP_H
#define BISHOP_H
#include "Pieces/Piece.h"
#include <cmath> // for abs()
#include "Board.h"


class Bishop : public Piece {
public:
    Bishop(bool isWhite); // constructor
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override; // check if the movement is valid
    virtual std::unique_ptr<Piece> clone() const override { return std::make_unique<Bishop>(*this); } // for cloning the piece
};
#endif // BISHOP_H
