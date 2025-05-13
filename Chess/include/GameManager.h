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

using namespace std;
class GameManager
{
private:
    Board* board; // Pointer to the chess board
    vector<Piece*> pieces; // Store all pieces
    int codeResponse;
    string playerColor;
    string opponentColor;

public:
    GameManager();
    ~GameManager();

    void initGame();
    void setCodeResponse(int code);
    int getCodeResponse() const;
    bool isCheck() const;
    string getInput();
    void displayBoard() const;
    void makeMove(const string& move);
    bool isValidMove(const string& move) const;
    bool isCheckmate() const;
    bool isStalemate() const;
    void switchTurn();
    int validateMove(std::string input, int playerIsWhite); // Validate the move based on the input string

    const Board& currentBoard() const { return *board; } // Get the current board state

}

#endif // GAMEMANAGER_H
;