#include "Pieces/Queen.h"
#include "Board.h"
#include <cmath> // for abs()

// constructor
Queen::Queen(bool isWhite) : Piece(isWhite) {
    this->setSymbol(isWhite ? 'q' : 'Q');
    this->setIsAlive(true);
    this->setIsWhite(isWhite);
}

// move validation
bool Queen::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const
{
    // A queen's move must be either straight (like a rook) or diagonal (like a bishop)
    const bool isStraight = (srcRow == destRow || srcCol == destCol);
    const bool isDiagonal = (std::abs(destRow - srcRow) == std::abs(destCol - srcCol));

    if (!isStraight && !isDiagonal)
    {
        return false; // If it's neither, it's an illegal move
    }

    // Determine the direction of the move (1, -1, or 0 for each axis)
    const int stepR = (destRow > srcRow) ? 1 : ((destRow < srcRow) ? -1 : 0);
    const int stepC = (destCol > srcCol) ? 1 : ((destCol < srcCol) ? -1 : 0);

    // Check that the path between the source and destination is clear of other pieces
    int r = srcRow + stepR;
    int c = srcCol + stepC;
    while (r != destRow || c != destCol)
    {
        if (board.getPiece(r, c) != nullptr)
        {
            return false; // The path is blocked
        }
        r += stepR;
        c += stepC;
    }

    // Check the destination square
    const Piece* destPiece = board.getPiece(destRow, destCol);
    if (destPiece == nullptr)
    {
        return true; // Valid move if the destination is empty
    }
    else
    {
        // Valid move if the destination contains an opponent's piece
        return destPiece->getIsWhite() != this->getIsWhite();
    }
}