#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(bool isWhite); // constructor
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override; // check if the movement is valid
    bool isValidCapture(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const; // check if the capture is valid
};
#endif // PAWN_H