#include "Rook.h"
#include "Board.h"
#include <cmath> // for abs()


Rook::Rook(bool isWhite) : Piece(isWhite) {
    char symbol = isWhite ? 'R' : 'r'; // Assign symbol based on color
    this->setSymbol(symbol); // Set the symbol for the piece
    this->setIsAlive(true); // Rook is alive when created
    this->setIsWhite(isWhite); // Set the color of the piece
}


bool Rook::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    if (srcRow != destRow && srcCol != destCol)
        return false; // must move in straight lines

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

    // Valid rook move
    return true;
}
