#include "Bishop.h"


Bishop::Bishop(bool isWhite) : Piece(isWhite) {
    symbol = isWhite ? 'B' : 'b'; // Assign symbol based on color
    isAlive = true; // Bishop is alive when created
}

bool Bishop::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // Check if the move is diagonal
    if (abs(srcRow - destRow) != abs(srcCol - destCol)) {
        return false; // Invalid move
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

    // Valid bishop move
    return true;
}
