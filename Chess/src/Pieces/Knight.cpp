#include "Knight.h"
#include "Board.h"
#include <cmath> // for abs()

Knight::Knight(bool isWhite) : Piece(isWhite) {
    char symbol = isWhite ? 'N' : 'n'; // Assign symbol based on color
    bool isAlive = true; // Knight is alive when created
    this->setSymbol(symbol); // Set the symbol for the piece
    this->setIsAlive(isAlive); // Set the alive status for the piece
    this->setIsWhite(isWhite); // Set the color of the piece
}

bool Knight::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // Check if the move is in an L-shape
    if ((abs(srcRow - destRow) == 2 && abs(srcCol - destCol) == 1) ||
        (abs(srcRow - destRow) == 1 && abs(srcCol - destCol) == 2)) {
        return true; // Valid knight move
    }
    return false; // Invalid move
}

