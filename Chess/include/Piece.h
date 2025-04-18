#ifndef PIECE_H
#define PIECE_H

#include <string>

class Board;

class Piece { // Abstract base class for chess pieces
protected:
    bool isWhite;
    bool isAlive;
    char symbol;

public:
    Piece(bool isWhite) : isWhite(isWhite) {}
    virtual ~Piece() = default;
    
    bool getColor() const { return isWhite; }

    // Check if this piece can move from src to dest
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const = 0;

    // getters and setters
    bool getIsAlive() const { return isAlive; }
    void setIsAlive(bool alive) { isAlive = alive; }
    void setSymbol(char sym) { symbol = sym; }
    char getSymbol() const { return symbol; }
    bool getIsWhite() const { return isWhite; }
    void setIsWhite(bool white) { isWhite = white; }
};

#endif // PIECE_H
