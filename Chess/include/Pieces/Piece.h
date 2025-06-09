#ifndef PIECE_H
#define PIECE_H

#include "Utils/CMove.h"
#include <memory>
#include <vector>
#include <cctype>      // std::islower

class Board;

/* Lower-case symbol = White side on THIS board */
inline bool symIsWhite(char ch)
{
    return std::islower(static_cast<unsigned char>(ch));
}

class Piece   // abstract base
{
private:
    bool isWhite;      // legacy flag (not used by AI any more)
    bool isAlive{true};
    char symbol{' '};

public:
    explicit Piece(bool white) : isWhite(white) {}
    virtual ~Piece() = default;

    // piece-specific movement rule
    virtual bool isValidMove(int sr,int sc,int dr,int dc,
                             const Board& b) const = 0;
    virtual std::unique_ptr<Piece> clone() const = 0;

    // trivial accessors
    bool  getIsAlive() const { return isAlive; }
    void  setIsAlive(bool v) { isAlive = v;    }

    char  getSymbol() const { return symbol;          }
    void  setSymbol(char s){ symbol = s;              }

    bool  getIsWhite() const { return isWhite;        }
    void  setIsWhite(bool v) { isWhite = v;           }

    /* --------------------------------------------------------------
       Default helper: enumerate every destination square and keep
       only those that pass the concrete piece’s isValidMove() check.
       NOTE:  we **do not** consult Board::getPiece here; callers
       (Board::generateLegalMoves, BestMoveFinder) already filter out
       self-captures and illegal moves that leave the king in check.
       --------------------------------------------------------------*/
    virtual std::vector<CMove>
    legalMoves(int r,int c,const Board& b) const
    {
        std::vector<CMove> out;
        for (int dr=0; dr<8; ++dr)
            for (int dc=0; dc<8; ++dc)
            {
                if (dr==r && dc==c) continue;          // same square
                if (isValidMove(r,c,dr,dc,b))
                    out.emplace_back(r,c,dr,dc);
            }
        return out;
    }
};

#endif  // PIECE_H
