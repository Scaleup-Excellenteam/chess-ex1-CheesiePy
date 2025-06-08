#ifndef PIECE_H
#define PIECE_H
#include "Utils/CMove.h"
#include <memory>
#include <vector>


class Board;

class Piece { // Abstract base class for chess pieces
private:
    bool isWhite;
    bool isAlive;
    char symbol;

public:
    Piece(bool isWhite) : isWhite(isWhite) {}
    virtual ~Piece() = default;
    
    // Check if this piece can move from src to dest
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const = 0;
    virtual std::unique_ptr<Piece> clone() const = 0; // for cloning the piece
    // getters and setters
    bool getIsAlive() const { return isAlive; }
    void setIsAlive(bool alive) { isAlive = alive; }
    void setSymbol(char sym) { symbol = sym; }
    char getSymbol() const { return symbol; }
    bool getIsWhite() const { return isWhite; }
    void setIsWhite(bool white) { isWhite = white; }


    
    /* Needed by BestMoveFinder
       Board must expose generateLegalMoves already, so by default
       every piece can delegate to Board. */
//  Chess/include/Pieces/Piece.h
virtual std::vector<CMove>
legalMoves(int r, int c, const Board& b) const
{
    std::vector<CMove> out;
    for (int dr = 0; dr < 8; ++dr)
        for (int dc = 0; dc < 8; ++dc)
        {
            if (dr == r && dc == c)        // ← NEW: don’t stand still
                continue;

            if (isValidMove(r, c, dr, dc, b))
                out.emplace_back(r, c, dr, dc);
        }
    return out;
}

};

#endif // PIECE_H
