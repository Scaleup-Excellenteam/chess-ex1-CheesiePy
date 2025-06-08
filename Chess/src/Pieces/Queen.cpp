#include "Pieces/Queen.h"
#include "Board.h"
#include <cmath> // for abs()
Queen::Queen(bool isWhite) : Piece(isWhite) {
    char symbol = isWhite ? 'Q' : 'q'; // Assign symbol based on color
    bool isAlive = true; // Queen is alive when created
    this->setSymbol(symbol); // Set the symbol for the piece
    this->setIsAlive(isAlive); // Set the alive status for the piece
    this->setIsWhite(isWhite); // Set the color of the piece
}

bool Queen::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // Check if the move is in a straight line or diagonal
    if (srcRow != destRow && srcCol != destCol && abs(srcRow - destRow) != abs(srcCol - destCol)) {
        return false; // Invalid move
    }
    // Check if the destination is occupied by a piece of the same color
    Piece* destPiece = board.getPiece(destRow, destCol);
    if (destPiece != nullptr && destPiece->getIsWhite() == this->getIsWhite()) {
        return false; // Cannot capture own piece
    }
    // Check path is clear
    int rowStep = (destRow - srcRow == 0) ? 0 : (destRow - srcRow) / abs(destRow - srcRow);
    int colStep = (destCol - srcCol == 0) ? 0 : (destCol - srcCol) / abs(destCol - srcCol);

    int row = srcRow + rowStep;
    int col = srcCol + colStep;

    while (row != destRow || col != destCol) {
        if (board.getPiece(row, col) != nullptr)
            return false; // path blocked
        row += rowStep;
        col += colStep;
    }

    // Valid queen move
    return true;
}