// chess game manager header file

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <iostream>
#include <string>
#include <vector>


#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"


class GameManager
{
    
private:
    Board* board; // Pointer to the chess board
    std::vector<Piece*> pieces; // Store all pieces
    int codeResponse;
    std::string playerColor;
    std::string opponentColor;

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
    bool isValidMove(const std::string& move) const;
    bool isCheckmate() const;
    bool isStalemate() const;
    void switchTurn();
    int validateMove(std::string input, int playerIsWhite); // Validate the move based on the input string

    const Board& currentBoard() const { return *board; } // Get the current board state

}

#endif // GAMEMANAGER_H
;