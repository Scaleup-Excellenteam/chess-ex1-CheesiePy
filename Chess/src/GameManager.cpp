#include "GameManager.h"

// ——— constructor ———
GameManager::GameManager()
  : board(nullptr),
    codeResponse(-1),
    isWhiteTurn_(true)
{
    initGame();
}

// ——— initGame ———
void GameManager::initGame()
{

    /* 1. fresh board ------------------------------------------- */
    board = std::make_unique<Board>();

    /* 2. fresh piece registry ---------------------------------- */
    pieces.clear();
    pieces.reserve(32);

    /* helper: push raw pointer into pieces[] and pass unique_ptr to Board */
    auto put = [this](int row, int col, Piece* raw)
    {
        pieces.push_back(raw);
        board->setPiece(row, col, std::unique_ptr<Piece>(raw));
    };

    /* 3. Black back rank (row 0) – UPPER-case symbols ----------- */
    put(0, 0, new Rook  (false));   // A8
    put(0, 1, new Knight(false));   // B8
    put(0, 2, new Bishop(false));   // C8
    put(0, 3, new Queen (false));   // D8
    put(0, 4, new King  (false));   // E8
    put(0, 5, new Bishop(false));   // F8
    put(0, 6, new Knight(false));   // G8
    put(0, 7, new Rook  (false));   // H8

    /* 4. Black pawns (row 1) ----------------------------------- */
    for (int c = 0; c < 8; ++c)
        put(1, c, new Pawn(false));           // A7 .. H7

    /* 5. White pawns (row 6) – lower-case symbols -------------- */
    for (int c = 0; c < 8; ++c)
        put(6, c, new Pawn(true));            // A2 .. H2

    /* 6. White back rank (row 7) ------------------------------- */
    put(7, 0, new Rook  (true));    // A1
    put(7, 1, new Knight(true));    // B1
    put(7, 2, new Bishop(true));    // C1
    put(7, 3, new Queen (true));    // D1
    put(7, 4, new King  (true));    // E1
    put(7, 5, new Bishop(true));    // F1
    put(7, 6, new Knight(true));    // G1
    put(7, 7, new Rook  (true));    // H1
}


GameManager::~GameManager()
{
    board.reset(); // Automatically cleans up the board and pieces
    pieces.clear(); // Clear the vector of pieces
}

void GameManager::setCodeResponse(int code)
{
    codeResponse = code;
}

int GameManager::getCodeResponse() const
{
    return codeResponse;
}


// ——— isCheck ———
// return true if the current player's king is in check
bool GameManager::isCheck() const
{
    bool whiteToMove = isWhiteTurn_;
    return board->inCheck(whiteToMove);
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
    int playerIsWhite = whiteToMove() ? 1 : 0;
    int code = validateMove(move);
    setCodeResponse(code);
    if (code == 42 || code == 41) {

        isWhiteTurn_ = !isWhiteTurn_; // switch turn only on legal moves
    }
}

bool GameManager::makeMove(int srcRow, int srcCol, int destRow, int destCol)
{
    if (!board) return false;

    Piece* moving = board->getPiece(srcRow, srcCol);
    if (!moving) return false;                 // should never happen

    /* Take ownership of the source square’s unique_ptr */
    std::unique_ptr<Piece> tmp = board->removePiece(srcRow, srcCol);

    /* If destination holds an opponent piece, it is automatically deleted
       when we overwrite the unique_ptr in that square. */
    board->setPiece(destRow, destCol, std::move(tmp));
    isWhiteTurn_ = !isWhiteTurn_; // switch turn

    return true;
    
}

// ——— isValidMove ———
// check move legality without mutating the board by looking at generateLegalMoves


int GameManager::validateMove(const std::string& mv) const
{
    if (mv.size() != 4) return 11; // Invalid format

    // --- CORRECTED COORDINATE LOGIC ---
    // The file ('a'-'h') is the column.
    int sC = mv[0] - 'a';
    int dC = mv[2] - 'a';

    // The rank ('1'-'8') is the row. Rank '1' is row 7, Rank '8' is row 0.
    int sR = 7 - (mv[1] - '1');
    int dR = 7 - (mv[3] - '1');
    // --- END CORRECTION ---

    if (sR < 0 || sR >= 8 || sC < 0 || sC >= 8 || dR < 0 || dR >= 8 || dC < 0 || dC >= 8) return 11; // Out of bounds

    Piece* src = board->getPiece(sR, sC);
    if (!src) return 11;                           // no piece
    if (src->getIsWhite() != isWhiteTurn_) return 12; // opponent’s piece

    if (auto dst = board->getPiece(dR, dC);
        dst && dst->getIsWhite() == src->getIsWhite()) return 13; // own piece

    if (!src->isValidMove(sR, sC, dR, dC, *board)) return 21; // piece-specific rule

    // TODO: if you add king-in-check detection, return 41 here.
    return 42;                                      // legal & safe
}

// ——— isCheckmate ———
// checkmate: side to move is in check and has no legal replies
bool GameManager::isCheckmate() const
{
    bool whiteToMove = isWhiteTurn_;
    if (!board->inCheck(whiteToMove)) return false;
    auto legal = board->generateLegalMoves(whiteToMove);
    return legal.empty();
}

// ——— isStalemate ———
// stalemate: side to move is not in check but has no legal replies
bool GameManager::isStalemate() const
{
    bool whiteToMove = isWhiteTurn_;
    if (board->inCheck(whiteToMove)) return false;
    auto legal = board->generateLegalMoves(whiteToMove);
    return legal.empty();
}