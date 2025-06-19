#ifndef ROOK_H
#define ROOK_H

#include "Pieces/Piece.h"

class Rook : public Piece {
    private:
        bool hasMoved_ = false;
    public:
        Rook(bool isWhite); // constructor
        bool getHasMoved() const { return hasMoved_; }
        void setHasMoved(bool moved) { hasMoved_ = moved; }
        virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override; // check if the movement is valid
        virtual std::unique_ptr<Piece> clone() const override { auto r = std::make_unique<Rook>(*this); r->setHasMoved(this->getHasMoved()); return r; } // for cloning the piece
    };
#endif // ROOK_H
