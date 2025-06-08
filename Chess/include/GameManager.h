// chess game manager header file

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <iostream>
#include <string>
#include <vector>


#include "Board.h"
#include "Pieces/Piece.h"
#include "Pieces/Rook.h"
#include "Pieces/King.h"
#include "Pieces/Queen.h"
#include "Pieces/Bishop.h"
#include "Pieces/Pawn.h"
#include "Pieces/Knight.h"


class GameManager
{
    
private:
    std::unique_ptr<Board> board; // Pointer to the chess board
    std::vector<Piece*> pieces; // Store all pieces
    bool isWhiteTurn_ = true; // True if it's white's turn, false for black
    int codeResponse;


public:
    GameManager();
    ~GameManager();

    void initGame();
    void setCodeResponse(int code);
    int getCodeResponse() const;
    bool isCheck() const;
    std::string getInput();
    void displayBoard() const;
    void makeMove(const std::string& move);
    bool makeMove(int srcRow, int srcCol, int destRow, int destCol);
    int validateMove(const std::string &mv) const;
    const Board &currentBoard() const { return *board; }
    bool isValidMove(const std::string& move) const;
    bool isCheckmate() const;
    bool isStalemate() const;

    bool whiteToMove() const { return isWhiteTurn_; }
};

#endif // GAMEMANAGER_H
