#include "Board.h"
#include "Pawn.h"


Board::Board() {
    grid.reserve(8); // optional but avoids reallocations
    for (int i = 0; i < 8; ++i) {
        grid.emplace_back(8); // each row has 8 null unique_ptrs
    }
}

// --- copy constructor ---
Board::Board(const Board& other) {
    grid.reserve(8);
    // create an 8×8 grid of empty slots
    for (int r = 0; r < 8; ++r)
        grid.emplace_back(8);

    // deep‐clone each piece via its virtual clone()
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = other.getPiece(r, c);
            if (p)
                grid[r][c] = p->clone();
        }
    }
}

// --- copy assignment operator ---
Board& Board::operator=(const Board& rhs) {
    if (this != &rhs) {
        // reset ourselves
        grid.clear();
        grid.reserve(8);
        for (int r = 0; r < 8; ++r)
            grid.emplace_back(8);

        // deep‐clone each piece
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                Piece* p = rhs.getPiece(r, c);
                if (p)
                    grid[r][c] = p->clone();
            }
        }
    }
    return *this;
}

// --- generate all legal moves for the given side (no self‐checks) ---
std::vector<CMove> Board::generateLegalMoves(bool whiteToMove) const {
    std::vector<CMove> moves;

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = getPiece(r, c);
            if (!p || p->getIsWhite() != whiteToMove)
                continue;

            for (int dr = 0; dr < 8; ++dr) {
                for (int dc = 0; dc < 8; ++dc) {
                    if (dr == r && dc == c) 
                        continue;

                    Piece* target = getPiece(dr, dc);
                    bool valid = false;

                    // pawn: distinguish between move vs. capture
                    if (Pawn* pawn = dynamic_cast<Pawn*>(p)) {
                        if (!target && pawn->isValidMove(r, c, dr, dc, *this))
                            valid = true;
                        else if (target && pawn->isValidCapture(r, c, dr, dc, *this))
                            valid = true;
                    } 
                    // all other pieces
                    else if (p->isValidMove(r, c, dr, dc, *this)) {
                        valid = true;
                    }

                    if (!valid) 
                        continue;

                    // simulate and ensure we don't leave our king in check
                    Board copy = *this;
                    copy.applyMove({r, c, dr, dc});
                    if (!copy.inCheck(whiteToMove))
                        moves.push_back({r, c, dr, dc});
                }
            }
        }
    }

    return moves;
}

// --- apply a move (mutates this Board) ---
void Board::applyMove(CMove m) {
    // take ownership of the moving piece
    std::unique_ptr<Piece> moving = removePiece(m.srcRow, m.srcCol);
    // overwrite any captured piece and place the mover
    grid[m.destRow][m.destCol] = std::move(moving);
}


// --- is the given side’s king in check? ---
bool Board::inCheck(bool whiteKing) const {
    // locate the king
    int kingR = -1, kingC = -1;
    char kingSym = whiteKing ? 'K' : 'k';
    for (int r = 0; r < 8 && kingR < 0; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = getPiece(r, c);
            if (p && p->getSymbol() == kingSym) {
                kingR = r; kingC = c;
                break;
            }
        }
    }
    if (kingR < 0)
        return false; // no king found => not in check

    // see if any enemy piece attacks that square
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = getPiece(r, c);
            if (p && p->getIsWhite() != whiteKing) {
                // pawn captures are special
                if (Pawn* pawn = dynamic_cast<Pawn*>(p)) {
                    if (pawn->isValidCapture(r, c, kingR, kingC, *this))
                        return true;
                } else if (p->isValidMove(r, c, kingR, kingC, *this)) {
                    return true;
                }
            }
        }
    }
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

