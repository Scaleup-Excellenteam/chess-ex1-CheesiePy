#include "Pieces/King.h"
#include "Board.h"
#include <cmath> // for abs()


King::King(bool isWhite) : Piece(isWhite) {
    char symbol = isWhite ? 'K' : 'k'; // Assign symbol based on color
    bool isAlive = true; // King is alive when created
    this->setSymbol(symbol); // Set the symbol for the piece
    this->setIsAlive(isAlive); // Set the alive status for the piece
    this->setIsWhite(isWhite); // Set the color of the piece
}

bool King::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // Check if the move is within one square in any direction
    if (abs(srcRow - destRow) <= 1 && abs(srcCol - destCol) <= 1) {
        return true; // Valid king move
    }
    //TODO: check if the destination square is occupied by a piece of different color

    return false; // Invalid move
}

bool King::isInCheck(int row, int col, const Board& board) const {
    // Check if the king is in check
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* piece = board.getPiece(r, c);
            if (piece != nullptr && piece->getIsWhite() != this->getIsWhite() && piece->isValidMove(r, c, row, col, board)) {
                return true; // King is in check
            }
        }
    }
    return false; // King is not in check
}

bool King::isInCheckmate(int row, int col, const Board& board) const {
    // Check if the king is in checkmate
    if (!isInCheck(row, col, board)) {
        return false; // Not in checkmate if not in check
    }

    // Check all possible moves for the king
    for (int r = row - 1; r <= row + 1; ++r) {
        for (int c = col - 1; c <= col + 1; ++c) {
            if (r >= 0 && r < 8 && c >= 0 && c < 8) {
                if (isValidMove(row, col, r, c, board) && !isInCheck(r, c, board)) {
                    return false; // Found a valid move that is not in check
                }
            }
        }
    }

    return true; // King is in checkmate
}

// check if the king is in stalemate

bool King::isInStalemate(int row, int col, const Board& board) const {
    // Check if the king is in stalemate
    if (isInCheck(row, col, board)) {
        return false; // Not in stalemate if in check
    }

    // Check all possible moves for the king
    for (int r = row - 1; r <= row + 1; ++r) {
        for (int c = col - 1; c <= col + 1; ++c) {
            if (r >= 0 && r < 8 && c >= 0 && c < 8) {
                if (isValidMove(row, col, r, c, board) && !isInCheck(r, c, board)) {
                    return false; // Found a valid move that is not in check
                }
            }
        }
    }

    return true; // King is in stalemate
}
