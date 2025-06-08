#include "Pieces/Queen.h"
#include "Board.h"
#include "Pieces/Rook.h"
#include "Pieces/Bishop.h"
#include <cmath> // for abs()
Queen::Queen(bool isWhite) : Piece(isWhite) {
    char symbol = isWhite ? 'q' : 'Q'; // Assign symbol based on color
    bool isAlive = true; // Queen is alive when created
    this->setSymbol(symbol); // Set the symbol for the piece
    this->setIsAlive(isAlive); // Set the alive status for the piece
    this->setIsWhite(isWhite); // Set the color of the piece
}

bool Queen::isValidMove(int srcRow,int srcCol,
                        int destRow,int destCol,
                        const Board& board) const
{
    if (srcRow == destRow || srcCol == destCol)       // rook-like
        return Rook(true).isValidMove(srcRow, srcCol, destRow, destCol, board);

    if (std::abs(destRow - srcRow) == std::abs(destCol - srcCol)) // bishop-like
        return Bishop(true).isValidMove(srcRow, srcCol, destRow, destCol, board);

    return false;
}
