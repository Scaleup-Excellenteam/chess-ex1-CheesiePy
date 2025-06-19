#ifndef PAWN_H
#define PAWN_H
#include "Pieces/Piece.h"

class Pawn : public Piece {
public:
    Pawn(bool isWhite); // constructor
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override; // check if the movement is valid
    virtual std::unique_ptr<Piece> clone() const override { return std::make_unique<Pawn>(*this); } // for cloning the piece
    bool isValidCapture(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const; // check if the capture is valid
};
#endif // PAWN_H