#include "Board.h"
#include "Pieces/Pawn.h"
#include <cassert>      // assert

/* ───────────────────────────── Constructors ─────────────────────────── */

Board::Board()
{
    grid.reserve(8);
    for (int r = 0; r < 8; ++r)
        grid.emplace_back(8);            // 8 null unique_ptrs
}

/* deep copy (clone each Piece) */
Board::Board(const Board& other)
{
    grid.reserve(8);
    for (int r = 0; r < 8; ++r)
        grid.emplace_back(8);

    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            if (const Piece* p = other.getPiece(r, c))
                grid[r][c] = p->clone();
}

/* copy-assignment */
Board& Board::operator=(const Board& rhs)
{
    if (this == &rhs) return *this;

    grid.clear();
    grid.reserve(8);
    for (int r = 0; r < 8; ++r)
        grid.emplace_back(8);

    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            if (const Piece* p = rhs.getPiece(r, c))
                grid[r][c] = p->clone();

    history.clear();
    return *this;
}

/* ─────────────────────── AI helpers (pseudo-legal) ──────────────────── */

std::vector<CMove> Board::generateLegalMoves(bool whiteToMove) const
{
    std::vector<CMove> moves;

    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
        {
            Piece* p = getPiece(r, c);
            if (!p || p->getIsWhite() != whiteToMove)        // engine’s colour
                continue;

            for (int dr = 0; dr < 8; ++dr)
                for (int dc = 0; dc < 8; ++dc)
                {
                    if (dr == r && dc == c) continue;

                    Piece* target = getPiece(dr, dc);
                    bool   ok     = false;

                    if (auto* pawn = dynamic_cast<Pawn*>(p))
                    {
                        if (!target && pawn->isValidMove   (r,c,dr,dc,*this)) ok = true;
                        if ( target && pawn->isValidCapture(r,c,dr,dc,*this)) ok = true;
                    }
                    else if (p->isValidMove(r, c, dr, dc, *this))
                        ok = true;

                    if (!ok) continue;

                    Board copy = *this;
                    copy.applyMove({r,c,dr,dc});
                    if (!copy.inCheck(whiteToMove))
                        moves.emplace_back(r,c,dr,dc);
                }
        }
    return moves;
}

/* ───────────────────────── apply / undo moves ──────────────────────── */

void Board::applyMove(const CMove& m)
{
    auto& src = grid[m.srcRow ][m.srcCol ];
    auto& dst = grid[m.destRow][m.destCol];

    /* save captured piece (if any) */
    history.push_back(MoveRecord{ m, std::move(dst) });

    /* move piece */
    dst = std::move(src);
}

void Board::undoMove(const CMove& m)
{
    assert(!history.empty() && "undoMove called on empty history!");

    MoveRecord rec = std::move(history.back());
    history.pop_back();

#ifndef NDEBUG
    assert(rec.mv.srcRow  == m.srcRow  && rec.mv.srcCol  == m.srcCol &&
           rec.mv.destRow == m.destRow && rec.mv.destCol == m.destCol);
#endif

    auto& src = grid[rec.mv.srcRow ][rec.mv.srcCol ];
    auto& dst = grid[rec.mv.destRow][rec.mv.destCol];

    src = std::move(dst);              // move piece back
    dst = std::move(rec.captured);     // restore captured (if any)
}

/* ─────────────────────── check detection ───────────────────────────── */

bool Board::inCheck(bool whiteKing) const
{
    /* locate king */
    int kR=-1, kC=-1;
    char kSym = whiteKing ? 'K':'k';

    for (int r=0; r<8 && kR<0; ++r)
        for (int c=0; c<8; ++c)
            if (const Piece* p = getPiece(r,c); p && p->getSymbol()==kSym)
            { kR=r; kC=c; break; }

    if (kR<0) return false;            // missing king (!)

    /* see if any opponent piece attacks it */
    for (int r=0;r<8;++r)
        for (int c=0;c<8;++c)
            if (Piece* p = getPiece(r,c); p && p->getIsWhite()!=whiteKing)
            {
                if (auto* pawn = dynamic_cast<Pawn*>(p))
                {
                    if (pawn->isValidCapture(r,c,kR,kC,*this))
                        return true;
                }
                else if (p->isValidMove(r,c,kR,kC,*this))
                    return true;
            }
    return false;
}

/* ─────────────────────── utility accessors ─────────────────────────── */

Piece* Board::getPiece(int r,int c) const { return grid[r][c].get(); }

void Board::setPiece(int r,int c,std::unique_ptr<Piece> p)
{ grid[r][c] = std::move(p); }

std::unique_ptr<Piece> Board::removePiece(int r,int c)
{
    auto tmp = std::move(grid[r][c]);
    grid[r][c]=nullptr;
    return tmp;
}
