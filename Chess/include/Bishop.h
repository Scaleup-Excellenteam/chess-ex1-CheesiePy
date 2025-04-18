#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"
#include <string>
#include <iostream>
#include <cmath> // for abs()
#include "Board.h"


class Bishop : public Piece {
public:
    Bishop(bool isWhite); // constructor
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override; // check if the movement is valid
};
#endif // BISHOP_H
