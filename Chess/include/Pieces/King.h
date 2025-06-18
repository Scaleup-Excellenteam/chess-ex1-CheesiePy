#ifndef KING_H
#define KING_H

#include "Pieces/Piece.h"

class King : public Piece {
private:
    bool hasMoved_ = false;
public:
    King(bool isWhite); // constructor
    bool getHasMoved() const { return hasMoved_; }
    void setHasMoved(bool moved) { hasMoved_ = moved; }
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override; // check if the movement is valid
    virtual std::unique_ptr<Piece> clone() const override { auto k = std::make_unique<King>(*this); k->setHasMoved(this->getHasMoved()); return k; } // for cloning the piece
};
#endif // KING_H
