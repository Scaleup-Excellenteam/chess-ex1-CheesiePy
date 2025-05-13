#include "Board.h"

Board::Board() {
    grid.reserve(8); // optional but avoids reallocations
    for (int i = 0; i < 8; ++i) {
        grid.emplace_back(8); // each row has 8 null unique_ptrs
    }
}

Board::Board(const Board &other)
{
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (other.grid[i][j]) {
                grid[i][j] = other.grid[i][j]->clone(); // clone the piece
            } else {
                grid[i][j] = nullptr; // no piece
            }
        }
    }
}

Board &Board::operator=(const Board &rhs)
{
    // TODO: insert return statement here
    if (this != &rhs) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (rhs.grid[i][j]) {
                    grid[i][j] = rhs.grid[i][j]->clone(); // clone the piece
                } else {
                    grid[i][j] = nullptr; // no piece
                }
            }
        }
    }
    return *this;
}

std::vector<CMove> Board::generateLegalMoves(bool whiteToMove) const
{
    //TODO: implement this function
    // This function should return a vector of all legal moves for the given side.
    // You need to check each piece on the board and see if it can move to any valid position.
    return std::vector<CMove>();
}

void Board::applyMove(CMove m)
{
    //TODO: implement this function
    // This function should apply the move to the board.
    // You need to update the positions of the pieces and handle captures.
    // You may also need to handle special moves like castling and en passant.
}

bool Board::inCheck(bool whiteKing) const
{
    //TODO: implement this function
    // This function should check if the given side's king is in check.
    // You need to check if any of the opponent's pieces can attack the king's position.
    // You may need to iterate through all pieces on the board and check their valid moves.
    return false;
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

