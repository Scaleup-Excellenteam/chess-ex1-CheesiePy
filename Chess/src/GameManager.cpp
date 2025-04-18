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

int GameManager::validateMove(std::string input, int playerIsWhite) {
    // Convert input to row and column indices
    int srcRow = input[0] - 'a'; // Convert 'a' to 0, 'b' to 1, etc.
    int srcCol = input[1] - '1'; // Convert '1' to 0, '2' to 1, etc.
    int destRow = input[2] - 'a';
    int destCol = input[3] - '1';

    // Check if the source and destination are valid
    if (srcRow < 0 || srcRow >= 8 || srcCol < 0 || srcCol >= 8 ||
        destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8) {
        return 11; // Invalid move
    }

    Piece* piece = board->getPiece(srcRow, srcCol);
    if (piece == nullptr) {
        return 11; // No piece at source
    }

    if (piece->getIsWhite() != playerIsWhite) {
        return 12; // Piece belongs to opponent
    }

    if (board->getPiece(destRow, destCol) != nullptr) {
        return 13; // Destination occupied by own piece
    }

    if (!piece->isValidMove(srcRow, srcCol, destRow, destCol, *board)) {
        return 21; // Invalid move for the piece
    }

    // Move the piece
    board->setPiece(destRow, destCol, std::unique_ptr<Piece>(piece));
    board->removePiece(srcRow, srcCol);

    return 42; // Move successful
}