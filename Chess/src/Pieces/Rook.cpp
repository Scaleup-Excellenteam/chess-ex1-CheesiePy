#include "Pieces/Rook.h"
#include "Board.h"
#include <cmath> // for abs()


Rook::Rook(bool isWhite) : Piece(isWhite) {
    char symbol = isWhite ? 'r' : 'R'; // Assign symbol based on color
    this->setSymbol(symbol); // Set the symbol for the piece
    this->setIsAlive(true); // Rook is alive when created
    this->setIsWhite(isWhite); // Set the color of the piece
}


bool Rook::isValidMove(int srcRow,
                       int srcCol,
                       int destRow,
                       int destCol,
                       const Board& board) const
{
    /* Must stay in same row or same column */
    if (srcRow != destRow && srcCol != destCol)
        return false;

    /* Step direction */
    int stepR = (destRow > srcRow) - (destRow < srcRow);  // 1,-1,0
    int stepC = (destCol > srcCol) - (destCol < srcCol);

    /* Path must be clear (exclude destination square) */
    for (int r = srcRow + stepR, c = srcCol + stepC;
         r != destRow || c != destCol;
         r += stepR,    c += stepC)
    {
        if (board.getPiece(r, c) != nullptr)
            return false;
    }

    /* Destination either empty or opponent piece */
    const Piece* dst = board.getPiece(destRow, destCol);
    return dst == nullptr || dst->getIsWhite() != this->getIsWhite();
}

