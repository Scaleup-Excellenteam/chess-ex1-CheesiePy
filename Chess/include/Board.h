#ifndef BOARD_H
#define BOARD_H

#include "Pieces/Piece.h"
#include <memory>
#include <vector>
#include "Utils/CMove.h"
#include "Utils/MoveScorePair.h"




class Board {
private:
    std::vector<std::vector<std::unique_ptr<Piece>>> grid; // polymorphic container for pieces
    // Each cell can hold a unique_ptr to a Piece (or derived class)
    // This allows for different types of pieces (e.g., Rook, Knight) to be stored in the same container
    // and managed automatically.
    // The grid is a 2D vector, where each element is a unique_ptr to a Piece.

public:
    Board();

    Board(const Board& other);
    Board& operator=(const Board& rhs);


    // --- AI support functions ---

    /// return every move that side is allowed to make
    /// (i.e. no self‐checks, obey piece rules, castling, en‐passant, etc.)
    std::vector<CMove> generateLegalMoves(bool whiteToMove) const;

    /// mutate this Board by playing that move
    /// (you must update piece positions, captures, castling rights, en‐passant, etc.)
    void applyMove(CMove m);

    /// true if the given side’s king is currently in check
    bool inCheck(bool whiteKing) const;


    Piece* getPiece(int row, int col) const;
    void setPiece(int row, int col, std::unique_ptr<Piece> piece);

    std::unique_ptr<Piece> removePiece(int row, int col);
    // generate leageal moves for the piece at (row, col)
    
};

// Forward declaration for AI namespace
namespace AI
{
    using ::MoveScorePair;
    std::vector<MoveScorePair>
    findBestMoves(const Board& board, bool isWhite, int limit);
}

#endif // BOARD_H
