#ifndef PIECE_H
#define PIECE_H

#include <string>

class Board;

class Piece {
protected:
    bool isWhite;

public:
    Piece(bool isWhite) : isWhite(isWhite) {}
    virtual ~Piece() = default;

    virtual char getSymbol() const = 0;

    bool getColor() const { return isWhite; }

    // Check if this piece can move from src to dest
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const = 0;
};

#endif // PIECE_H
