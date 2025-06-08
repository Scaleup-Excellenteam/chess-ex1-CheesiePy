#include "Pieces/Bishop.h"


Bishop::Bishop(bool isWhite) : Piece(isWhite) {
    char symbol = isWhite ? 'b' : 'B'; // Assign symbol based on color
    bool isAlive = true; // Bishop is alive when created
    this->setSymbol(symbol); // Set the symbol for the piece
    this->setIsAlive(isAlive); // Set the alive status for the piece
}


bool Bishop::isValidMove(int srcRow,int srcCol,
                         int destRow,int destCol,
                         const Board& board) const
{
    if (std::abs(destRow - srcRow) != std::abs(destCol - srcCol))
        return false;                           // must stay on a diagonal

    int stepR = (destRow > srcRow) ? 1 : -1;
    int stepC = (destCol > srcCol) ? 1 : -1;

    for (int r = srcRow + stepR, c = srcCol + stepC;
         r != destRow;
         r += stepR, c += stepC)
        if (board.getPiece(r, c) != nullptr)
            return false;

    const Piece* dst = board.getPiece(destRow, destCol);
    return dst == nullptr || dst->getIsWhite() != this->getIsWhite();
}

