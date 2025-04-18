#include "Board.h"

Board::Board() {
    grid.reserve(8); // optional but avoids reallocations
    for (int i = 0; i < 8; ++i) {
        grid.emplace_back(8); // each row has 8 null unique_ptrs
    }
}

Piece* Board::getPiece(int row, int col) const {
    // Returns a raw pointer to the piece at the specified cell
    return grid[row][col].get();
}

void Board::setPiece(int row, int col, std::unique_ptr<Piece> piece) {
    // This function takes ownership of the piece
    // and places it in the specified cell of the grid.
    grid[row][col] = std::move(piece);
}

std::unique_ptr<Piece> Board::removePiece(int row, int col) {
    return std::move(grid[row][col]);
}

