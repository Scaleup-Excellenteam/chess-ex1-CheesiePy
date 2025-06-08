#include "Pieces/Pawn.h"
#include "Board.h"

Pawn::Pawn(bool isWhite) : Piece(isWhite) {
    char symbol = isWhite ? 'P' : 'p'; // Assign symbol based on color
    bool isAlive = true; // Pawn is alive when created
    this->setSymbol(symbol); // Set the symbol for the piece
    this->setIsAlive(isAlive); // Set the alive status for the piece
}

bool Pawn::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // Check if the move is forward
    if (this->getIsWhite()) { // White pawn moves up
        if (srcRow == 1 && destRow == 3 && srcCol == destCol && board.getPiece(destRow, destCol) == nullptr) {
            return true; // Two squares forward on first move
        }
        if (destRow == srcRow + 1 && srcCol == destCol && board.getPiece(destRow, destCol) == nullptr) {
            return true; // One square forward
        }
    } else { // Black pawn moves down
        if (srcRow == 6 && destRow == 4 && srcCol == destCol && board.getPiece(destRow, destCol) == nullptr) {
            return true; // Two squares forward on first move
        }
        if (destRow == srcRow - 1 && srcCol == destCol && board.getPiece(destRow, destCol) == nullptr) {
            return true; // One square forward
        }
    }
    return false; // Invalid move
}

bool Pawn::isValidCapture(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // Check if the move is diagonal
    if (this->getIsWhite()) {
        if (destRow == srcRow + 1 && (destCol == srcCol - 1 || destCol == srcCol + 1)) {
            Piece* destPiece = board.getPiece(destRow, destCol);
            return destPiece != nullptr && !destPiece->getIsWhite(); // Capture opponent's piece
        }
    } else {
        if (destRow == srcRow - 1 && (destCol == srcCol - 1 || destCol == srcCol + 1)) {
            Piece* destPiece = board.getPiece(destRow, destCol);
            return destPiece != nullptr && destPiece->getIsWhite(); // Capture opponent's piece
        }
    }
    return false; // Invalid capture
}