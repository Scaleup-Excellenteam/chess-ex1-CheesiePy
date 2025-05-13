#include "GameManager.h"

void GameManager::initGame()
{
    // initialize the board
    board = new Board();
    // initialize pieces
    pieces.clear(); // Clear any existing pieces
    pieces.reserve(32); // Reserve space for 32 pieces

    // Initialize pieces

    // rooks
    pieces.push_back(new Rook(true)); // White left Rook
    pieces.push_back(new Rook(true)); // White left Rook
    pieces.push_back(new Rook(false)); // Black left Rook
    pieces.push_back(new Rook(false)); // Black right Rook
    // kings
    pieces.push_back(new King(true)); // White King
    pieces.push_back(new King(false)); // Black King
    // queens
    pieces.push_back(new Queen(true)); // White Queen
    pieces.push_back(new Queen(false)); // Black Queen

    // bishops
    pieces.push_back(new Bishop(true)); // White Bishop left
    pieces.push_back(new Bishop(true)); // White Bishop right
    pieces.push_back(new Bishop(false)); // Black Bishop left
    pieces.push_back(new Bishop(false)); // Black Bishop right

    // knights
    pieces.push_back(new Knight(true)); // White left Knight
    pieces.push_back(new Knight(true)); // White right Knight
    pieces.push_back(new Knight(false)); // Black left Knight
    pieces.push_back(new Knight(false)); // Black right Knight


    // pawns 
    for (int i = 0; i < 8; ++i) {
        pieces.push_back(new Pawn(true)); // White Pawns
        pieces.push_back(new Pawn(false)); // Black Pawns
    }


    // Set up the initial positions of the pieces on the board
    //rooks
    board->setPiece(0, 0, std::unique_ptr<Piece>(pieces[0])); // White Rook at A1
    board->setPiece(0, 7, std::unique_ptr<Piece>(pieces[1])); // White Rook at H1
    board->setPiece(7, 0, std::unique_ptr<Piece>(pieces[2])); // Black Rook at A8
    board->setPiece(7, 7, std::unique_ptr<Piece>(pieces[3])); // Black Rook at H8

    // kings
    board->setPiece(0, 4, std::unique_ptr<Piece>(pieces[4])); // White King at A5
    board->setPiece(7, 4, std::unique_ptr<Piece>(pieces[5])); // Black King at H5

    //queens
    board->setPiece(0, 3, std::unique_ptr<Piece>(pieces[6])); // White Queen at A4
    board->setPiece(7, 3, std::unique_ptr<Piece>(pieces[7])); // Black Queen at H4

    // bishops
    board->setPiece(0, 2, std::unique_ptr<Piece>(pieces[8])); // White Bishop left at A3
    board->setPiece(0, 5, std::unique_ptr<Piece>(pieces[9])); // White Bishop right at A6
    board->setPiece(7, 2, std::unique_ptr<Piece>(pieces[10])); // Black Bishop left at H3
    board->setPiece(7, 5, std::unique_ptr<Piece>(pieces[11])); // Black Bishop right at H6
    
    // knights
    board->setPiece(0, 1, std::unique_ptr<Piece>(pieces[12])); // White left Knight at A2
    board->setPiece(0, 6, std::unique_ptr<Piece>(pieces[13])); // White right Knight at A7
    board->setPiece(7, 1, std::unique_ptr<Piece>(pieces[14])); // Black left Knight at H2
    board->setPiece(7, 6, std::unique_ptr<Piece>(pieces[15])); // Black right Knight at H7


    // pawns
    for (int i = 0; i < 8; ++i) {
        board->setPiece(1, i, std::unique_ptr<Piece>(pieces[12 + i])); // White Pawns at row 2
        board->setPiece(6, i, std::unique_ptr<Piece>(pieces[20 + i])); // Black Pawns at row 7
    }


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
}

void GameManager::setCodeResponse(int code)
{
    codeResponse = code;
}

int GameManager::getCodeResponse() const
{
    return codeResponse;
}
// TODO: Implement isCheck, isCheckmate, isStalemate, etc.


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
