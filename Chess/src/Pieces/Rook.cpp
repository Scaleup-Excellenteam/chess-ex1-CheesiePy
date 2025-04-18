#include "Rook.h"
#include "../../include/Board.h"

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
