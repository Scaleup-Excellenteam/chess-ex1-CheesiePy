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
        pieces.push_back(new Pawn(true)); // White Pawns (posision)
    }

    for (int i = 0; i < 8; ++i) {
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
        board->setPiece(1, i, std::unique_ptr<Piece>(pieces[16 + i])); // White Pawns at row 2
        board->setPiece(6, i, std::unique_ptr<Piece>(pieces[24 + i])); // Black Pawns at row 7
    }
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



// ——— constructor ———
GameManager::GameManager()
  : board(nullptr),
    codeResponse(-1),
    playerColor("white"),
    opponentColor("black")
{
    initGame();
}

// ——— isCheck ———
// return true if the current player's king is in check
bool GameManager::isCheck() const
{
    bool white = (playerColor == "white");
    return board->inCheck(white);
}

// ——— getInput ———
// simple wrapper to read a move string
std::string GameManager::getInput()
{
    std::string input;
    std::cin >> input;
    return input;
}

// ——— displayBoard ———
// print the board (rank 8 down to 1) using each piece's symbol or “. ”
void GameManager::displayBoard() const
{
    for (int r = 7; r >= 0; --r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = board->getPiece(r, c);
            if (p)
                std::cout << p->getSymbol() << ' ';
            else
                std::cout << ". ";
        }
        std::cout << "\n";
    }
}

// ——— makeMove ———
// validate & apply a move, set the codeResponse, and swap turns on success
void GameManager::makeMove(const std::string& move)
{
    int playerIsWhite = (playerColor == "white") ? 1 : 0;
    int code = validateMove(move, playerIsWhite);
    setCodeResponse(code);
    if (code == 42 || code == 41) {
        switchTurn();
    }
}

// ——— isValidMove ———
// check move legality without mutating the board by looking at generateLegalMoves
bool GameManager::isValidMove(const std::string& move) const
{
    if (move.size() != 4) return false;
    int srcRow  = move[0] - 'a';
    int srcCol  = move[1] - '1';
    int destRow = move[2] - 'a';
    int destCol = move[3] - '1';

    bool whiteToMove = (playerColor == "white");
    auto legal = board->generateLegalMoves(whiteToMove);
    for (const auto& m : legal) {
        if (m.srcRow  == srcRow  &&
            m.srcCol  == srcCol  &&
            m.destRow == destRow &&
            m.destCol == destCol)
        {
            return true;
        }
    }
    return false;
}

// ——— isCheckmate ———
// checkmate: side to move is in check and has no legal replies
bool GameManager::isCheckmate() const
{
    bool whiteToMove = (playerColor == "white");
    if (!board->inCheck(whiteToMove)) return false;
    auto legal = board->generateLegalMoves(whiteToMove);
    return legal.empty();
}

// ——— isStalemate ———
// stalemate: side to move is not in check but has no legal replies
bool GameManager::isStalemate() const
{
    bool whiteToMove = (playerColor == "white");
    if (board->inCheck(whiteToMove)) return false;
    auto legal = board->generateLegalMoves(whiteToMove);
    return legal.empty();
}

// ——— switchTurn ———
// swap the two color‐strings so the other side moves next
void GameManager::switchTurn()
{
    std::swap(playerColor, opponentColor);
}
