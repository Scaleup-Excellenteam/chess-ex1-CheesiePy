#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
    Rook(bool isWhite) : Piece(isWhite) {}

    char getSymbol() const override {
        return isWhite ? 'R' : 'r';
    }

    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override;
};

#endif // ROOK_H
