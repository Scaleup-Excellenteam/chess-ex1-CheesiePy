#ifndef BOARD_H
#define BOARD_H

#include "Pieces/Piece.h"
#include "Utils/CMove.h"
#include "Utils/MoveScorePair.h"
#include <memory>
#include <vector>

class Board
{
private:
    // 8×8 polymorphic container for pieces
    std::vector<std::vector<std::unique_ptr<Piece>>> grid;

    /* ─────────────── NEW: move-history stack ─────────────── */
    struct MoveRecord {
        CMove mv;                            // the move itself
        std::unique_ptr<Piece> captured;     // what was on dest before the move
    };
    std::vector<MoveRecord> history;         // LIFO stack (push in applyMove)

public:
    Board();
    Board(const Board& other);
    Board& operator=(const Board& rhs);

    // ─────────── AI support functions ───────────
    std::vector<CMove> generateLegalMoves(bool whiteToMove) const;
    void applyMove(const CMove& m);          // play a move  (push to history)
    void undoMove(const CMove& m);           // NEW: take it back (pop history)
    bool inCheck(bool whiteKing) const;

    // direct square access
    Piece* getPiece(int row, int col) const;
    void   setPiece(int row, int col, std::unique_ptr<Piece> piece);
    std::unique_ptr<Piece> removePiece(int row, int col);
};

/* ────── Forward declaration for AI namespace ────── */
namespace AI
{
    using ::MoveScorePair;
    std::vector<MoveScorePair>
    findBestMoves(const Board& board, bool isWhite, int limit);
}

#endif // BOARD_H
