#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include <string>
#include <iostream>
#include <cmath> // for abs()
#include "Board.h"
#include "Queen.h"


class Queen : public Piece {
public:
    Queen(bool isWhite); // constructor
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override; // check if the movement is valid
};
#endif // QUEEN_H