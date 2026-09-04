#include "Pieces/Knight.h"
#include "Board.h"
#include <cmath> // for abs()

Knight::Knight(bool isWhite) : Piece(isWhite) {
    char symbol = isWhite ? 'n' : 'N'; // Assign symbol based on color
    bool isAlive = true; // Knight is alive when created
    this->setSymbol(symbol); // Set the symbol for the piece
    this->setIsAlive(isAlive); // Set the alive status for the piece
    this->setIsWhite(isWhite); // Set the color of the piece
}

bool Knight::isValidMove(int srcRow,int srcCol,
                         int destRow,int destCol,
                         const Board& board) const
{
    int dr = std::abs(destRow - srcRow);
    int dc = std::abs(destCol - srcCol);

    if (!((dr == 1 && dc == 2) || (dr == 2 && dc == 1)))
        return false;

    const Piece* dst = board.getPiece(destRow, destCol);
    return dst == nullptr || dst->getIsWhite() != this->getIsWhite();
}

