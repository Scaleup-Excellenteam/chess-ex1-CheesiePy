#include "Pieces/Pawn.h"
#include "Board.h"

Pawn::Pawn(bool isWhite) : Piece(isWhite) {
    char symbol = isWhite ? 'p' : 'P'; // Assign symbol based on color
    bool isAlive = true; // Pawn is alive when created
    this->setSymbol(symbol); // Set the symbol for the piece
    this->setIsAlive(isAlive); // Set the alive status for the piece
}

bool Pawn::isValidMove(int sR,int sC,int dR,int dC,const Board& b) const
{
    const int dir  = getIsWhite() ? -1 : +1;   // white goes “up”  (row--)
    const int home = getIsWhite() ?  6 :  1;   // g-rank / b-rank start

    /* straight advance */
    if (dC == sC) {
        if (dR == sR + dir && b.getPiece(dR,dC) == nullptr)               return true;
        if (sR == home && dR == sR + 2*dir &&
            b.getPiece(sR+dir,sC) == nullptr && b.getPiece(dR,dC)==nullptr) return true;
    }
    /* diagonal capture */
    if (std::abs(dC - sC) == 1 && dR == sR + dir) {
        const Piece* tgt = b.getPiece(dR,dC);
        if (tgt && tgt->getIsWhite() != this->getIsWhite())               return true;
    }
    return false;
}

bool Pawn::isValidCapture(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    // Check if the move is diagonal
    if (this->getIsWhite()) {
        if (destRow == srcRow + 1 && (destCol == srcCol - 1 || destCol == srcCol + 1)) {
            Piece* destPiece = board.getPiece(destRow, destCol);
            return destPiece != nullptr && !destPiece->getIsWhite(); // Capture opponent's piece
        }
    } else {
        if (destRow == srcRow - 1 && (destCol == srcCol - 1 || destCol == srcCol + 1)) {
            Piece* destPiece = board.getPiece(destRow, destCol);
            return destPiece != nullptr && destPiece->getIsWhite(); // Capture opponent's piece
        }
    }
    return false; // Invalid capture
}