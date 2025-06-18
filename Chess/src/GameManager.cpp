#include "GameManager.h"
#include "Board.h"
#include "Pieces/Piece.h"
#include "Pieces/Rook.h"
#include "Pieces/King.h"
#include "Pieces/Queen.h"
#include "Pieces/Bishop.h"
#include "Pieces/Pawn.h"
#include "Pieces/Knight.h"
#include <memory>
#include <iostream>

GameManager::GameManager()
  : board(nullptr), codeResponse(-1), isWhiteTurn_(true)
{
    initGame();
}

GameManager::~GameManager()
{
    board.reset();
    pieces.clear();
}

void GameManager::initGame()
{
    board = std::make_unique<Board>();
    pieces.clear();
    pieces.reserve(32);
    auto put = [this](int row, int col, Piece* raw)
    {
        pieces.push_back(raw);
        board->setPiece(row, col, std::unique_ptr<Piece>(raw));
    };
    put(0, 0, new Rook(false)); put(0, 1, new Knight(false)); put(0, 2, new Bishop(false));
    put(0, 3, new Queen(false)); put(0, 4, new King(false)); put(0, 5, new Bishop(false));
    put(0, 6, new Knight(false)); put(0, 7, new Rook(false));
    for (int c = 0; c < 8; ++c) put(1, c, new Pawn(false));
    for (int c = 0; c < 8; ++c) put(6, c, new Pawn(true));
    put(7, 0, new Rook(true)); put(7, 1, new Knight(true)); put(7, 2, new Bishop(true));
    put(7, 3, new Queen(true)); put(7, 4, new King(true)); put(7, 5, new Bishop(true));
    put(7, 6, new Knight(true)); put(7, 7, new Rook(true));
}

void GameManager::setCodeResponse(int code) { codeResponse = code; }
int GameManager::getCodeResponse() const { return codeResponse; }
bool GameManager::isCheck() const { return board->inCheck(isWhiteTurn_); }
const Board& GameManager::currentBoard() const { return *board; }
bool GameManager::whiteToMove() const { return isWhiteTurn_; }

void GameManager::makeMove(const std::string& move)
{
    int code = validateMove(move);
    setCodeResponse(code);
    if (code == 42 || code == 41) {
        int sC = move[0] - 'a';
        int dC = move[2] - 'a';
        int sR = 7 - (move[1] - '1');
        int dR = 7 - (move[3] - '1');
        Piece* srcPiece = board->getPiece(sR, sC);
        Piece* dstPiece = board->getPiece(dR, dC);
        bool isPawnMove = srcPiece && (dynamic_cast<Pawn*>(srcPiece) != nullptr);
        bool isCapture = dstPiece != nullptr;
        std::unique_ptr<Piece> tmp = board->removePiece(sR, sC);
        board->setPiece(dR, dC, std::move(tmp));
        if (isPawnMove || isCapture) {
            resetFiftyMoveCounter();
        } else {
            incrementFiftyMoveCounter();
        }
        isWhiteTurn_ = !isWhiteTurn_;
    }
}

bool GameManager::makeMove(int srcRow, int srcCol, int destRow, int destCol)
{
    std::string move_str;
    move_str += (char)('a' + srcCol);
    move_str += (char)('1' + (7 - srcRow));
    move_str += (char)('a' + destCol);
    move_str += (char)('1' + (7 - destRow));
    makeMove(move_str);
    return (codeResponse == 41 || codeResponse == 42);
}

int GameManager::validateMove(const std::string& mv) const
{
    if (mv.size() != 4) return 11;
    int sC = mv[0] - 'a';
    int dC = mv[2] - 'a';
    int sR = 7 - (mv[1] - '1');
    int dR = 7 - (mv[3] - '1');
    if (sR < 0 || sR >= 8 || sC < 0 || sC >= 8 || dR < 0 || dR >= 8 || dC < 0 || dC >= 8) return 11;
    Piece* src = board->getPiece(sR, sC);
    if (!src) return 11;
    if (src->getIsWhite() != isWhiteTurn_) return 12;
    if (auto dst = board->getPiece(dR, dC); dst && dst->getIsWhite() == src->getIsWhite()) return 13;
    if (!src->isValidMove(sR, sC, dR, dC, *board)) return 21;
    Board copy = *board;
    std::unique_ptr<Piece> tmp = copy.removePiece(sR, sC);
    copy.setPiece(dR, dC, std::move(tmp));
    if (copy.inCheck(isWhiteTurn_)) return 31;
    if (copy.inCheck(!isWhiteTurn_)) return 41;
    return 42;
}

bool GameManager::isCheckmate() const
{
    if (!board->inCheck(isWhiteTurn_)) return false;
    return board->generateLegalMoves(isWhiteTurn_).empty();
}

bool GameManager::isStalemate() const
{
    if (board->inCheck(isWhiteTurn_)) return false;
    return board->generateLegalMoves(isWhiteTurn_).empty();
}