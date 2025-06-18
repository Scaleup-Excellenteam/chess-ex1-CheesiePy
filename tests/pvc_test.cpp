#include "GameManager.h"
#include "AI/BestMoveFinder.h" // Needed to call the AI
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

/**
 * @brief Tests the Player vs. Computer game flow for one round of moves.
 */
void test_pvc_opening_moves() {
    std::cout << "--- Running C++ Test: Player vs. Computer Mode ---" << std::endl;
    GameManager game;

    // --- 1. PLAYER'S TURN (WHITE) ---
    std::cout << "Simulating Player's move (e2e4)..." << std::endl;
    assert(game.whiteToMove() == true); // Verify it's White's turn
    game.makeMove("e2e4");

    // Assert that the move was successful and the turn switched to Black
    assert(game.getCodeResponse() == 42);
    assert(game.whiteToMove() == false);
    
    // Get the board state to verify the player's move later
    const Board& board_after_player_move = game.currentBoard();
    assert(board_after_player_move.getPiece(4, 4) != nullptr); // e4 has a piece
    assert(board_after_player_move.getPiece(4, 4)->getSymbol() == 'p'); // It's a white pawn


    // --- 2. COMPUTER'S TURN (BLACK) ---
    std::cout << "Simulating Computer's turn (AI will choose best move)..." << std::endl;
    
    // Call the AI to find the best move for Black
    auto bestMoves = AI::findBestMoves(game.currentBoard(), game.whiteToMove(), 1);

    // Assert that the AI found at least one move
    assert(!bestMoves.empty());

    CMove aiMove = bestMoves[0].move;
    std::cout << "AI chose move: " << bestMoves[0].toString() << std::endl;
    
    // Get the piece that the AI is about to move
    Piece* movingPiece = game.currentBoard().getPiece(aiMove.srcRow, aiMove.srcCol);
    assert(movingPiece != nullptr); // Make sure there is a piece to move
    char movingPieceSymbol = movingPiece->getSymbol();


    // Execute the AI's chosen move using the integer-based makeMove
    game.makeMove(aiMove.srcRow, aiMove.srcCol, aiMove.destRow, aiMove.destCol);

    // --- 3. VERIFY THE OUTCOME ---
    // Assert that the AI's move was successful and the turn switched back to White
    assert(game.getCodeResponse() == 42 || game.getCodeResponse() == 41);
    assert(game.whiteToMove() == true);

    const Board& board_after_ai_move = game.currentBoard();
    // Assert that the source square is now empty
    assert(board_after_ai_move.getPiece(aiMove.srcRow, aiMove.srcCol) == nullptr);
    // Assert that the destination square now contains the piece that was moved
    Piece* movedPiece = board_after_ai_move.getPiece(aiMove.destRow, aiMove.destCol);
    assert(movedPiece != nullptr);
    assert(movedPiece->getSymbol() == movingPieceSymbol);


    std::cout << "\n✅ SUCCESS: Player vs. Computer turn sequence works correctly." << std::endl;
}

int main() {
    try {
        test_pvc_opening_moves();
    } catch (const std::exception& e) {
        std::cerr << "❌ FAILURE: Test threw an exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ FAILURE: Test threw an unknown exception." << std::endl;
        return 1;
    }
    return 0;
}