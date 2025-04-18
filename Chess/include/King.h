#ifndef KING_H
#define KING_H

#include "Piece.h"
#include <string>
#include <iostream>


class King : public Piece {
public:
    King(bool isWhite); // constructor
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override; // check if the movement is valid
    virtual bool isInCheck(int row, int col, const Board& board) const; // check if the king is in check
    virtual bool isInCheckmate(int row, int col, const Board& board) const; // check if the king is in checkmate
};
#endif // KING_H
