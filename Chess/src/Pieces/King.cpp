#include "Pieces/King.h"
#include "Board.h"
#include <cmath> // for abs()


King::King(bool isWhite) : Piece(isWhite) {
    char symbol = isWhite ? 'k' : 'K'; // Assign symbol based on color
    bool isAlive = true; // King is alive when created
    this->setSymbol(symbol); // Set the symbol for the piece
    this->setIsAlive(isAlive); // Set the alive status for the piece
    this->setIsWhite(isWhite); // Set the color of the piece
}

bool King::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const
{
    // A king moves at most one square in any direction
    if (std::abs(srcRow - destRow) <= 1 && std::abs(srcCol - destCol) <= 1)
    {
        Piece* destPiece = board.getPiece(destRow, destCol);

        // Legal if the destination is empty or holds an opponent piece
        return destPiece == nullptr ||
               destPiece->getIsWhite() != this->getIsWhite();
    }

    return false; // Any other displacement is illegal for a king
}
