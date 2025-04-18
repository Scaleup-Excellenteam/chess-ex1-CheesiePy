#include "GameManager.h"

void GameManager::initGame()
{
    // initialize the board
    board = new Board();
    // initialize pieces
    pieces.push_back(new Rook(true)); // White left Rook
    pieces.push_back(new Rook(true)); // White left Rook
    pieces.push_back(new Rook(false)); // Black left Rook
    pieces.push_back(new Rook(false)); // Black right Rook

    // Set up the initial positions of the pieces on the board
    board->setPiece(0, 0, std::unique_ptr<Piece>(pieces[0])); // White Rook at A1
    board->setPiece(0, 7, std::unique_ptr<Piece>(pieces[1])); // White Rook at H1
    board->setPiece(7, 0, std::unique_ptr<Piece>(pieces[2])); // Black Rook at A8
    board->setPiece(7, 7, std::unique_ptr<Piece>(pieces[3])); // Black Rook at H8

    // Initialize other pieces similarly...
    // TODO: Add other pieces like Knights, Bishops, etc.   
}

GameManager::GameManager() : board(nullptr), codeResponse(0), playerColor("white"), opponentColor("black")
{
    initGame();
}

GameManager::~GameManager()
{
    delete board; // Clean up the board
    for (Piece* piece : pieces) {
        delete piece; // Clean up each piece
    }
}

void GameManager::setCodeResponse(int code)
{
    codeResponse = code;
}

int GameManager::getCodeResponse() const
{
    return codeResponse;
}
