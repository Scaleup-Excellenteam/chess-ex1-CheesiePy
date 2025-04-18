#include "Board.h"

Board::Board() {
    grid.reserve(8); // optional but avoids reallocations
    for (int i = 0; i < 8; ++i) {
        grid.emplace_back(8); // each row has 8 null unique_ptrs
    }
}
Piece* Board::getPiece(int row, int col) const {
    return grid[row][col].get();
}

void Board::setPiece(int row, int col, std::unique_ptr<Piece> piece) {
    grid[row][col] = std::move(piece);
}

std::unique_ptr<Piece> Board::removePiece(int row, int col) {
    return std::move(grid[row][col]);
}

