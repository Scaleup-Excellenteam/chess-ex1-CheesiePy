#include "GameManager.h"
#include "Board.h"
#include "Pieces/Piece.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

/**
 * @brief Tests a standard, legal kingside castling maneuver (O-O).
 */
void test_legal_kingside_castling() {
    std::cout << "--- Running C++ Test: Legal Kingside Castling ---" << std::endl;
    GameManager game;

    // 1. Set up the board by clearing the path between the King and Rook.
    const std::vector<std::string> setup_moves = {
        "e2e4", "e7e5", // Clear path for King and Queen
        "g1f3", "b8c6", // Move Knight
        "f1c4", "g8f6"  // Move Bishop
    };

    for (const auto& move : setup_moves) {
        game.makeMove(move);
    }

    // 2. Perform the kingside castle (move King from e1 to g1).
    std::cout << "Applying castling move: e1g1 for White" << std::endl;
    game.makeMove("e1g1");

    // 3. Assert the results.
    // The move must be considered legal.
    assert(game.getCodeResponse() == 42 || game.getCodeResponse() == 41);

    const Board& board = game.currentBoard();
    // The King should now be on g1 (row 7, col 6).
    Piece* king = board.getPiece(7, 6);
    assert(king != nullptr && king->getSymbol() == 'k');

    // The Rook should now be on f1 (row 7, col 5).
    Piece* rook = board.getPiece(7, 5);
    assert(rook != nullptr && rook->getSymbol() == 'r');

    // The original squares of the King and Rook should be empty.
    assert(board.getPiece(7, 4) == nullptr); // e1 is empty
    assert(board.getPiece(7, 7) == nullptr); // h1 is empty

    std::cout << "\n✅ SUCCESS: Legal castling move executed correctly." << std::endl;
}

/**
 * @brief Tests that castling is illegal if the King has previously moved.
 */
void test_illegal_castling_after_king_moved() {
    std::cout << "\n--- Running C++ Test: Illegal Castling (King Moved) ---" << std::endl;
    GameManager game;

    // 1. Set up the board, but move the king back and forth.
    const std::vector<std::string> setup_moves = {
        "e2e4", "e7e5",
        "e1e2", "e8e7", // Move kings
        "e2e1", "e7e8"  // Move kings back
    };
    for (const auto& move : setup_moves) {
        game.makeMove(move);
    }

    // 2. Attempt to castle after the path is cleared.
    const std::vector<std::string> setup_moves_2 = {"g1f3", "b8c6", "f1c4", "g8f6"};
    for (const auto& move : setup_moves_2) {
        game.makeMove(move);
    }

    std::cout << "Applying illegal castling move: e1g1 for White" << std::endl;
    game.makeMove("e1g1");

    // 3. Assert that the move was rejected.
    // The code should be an error code (like 21 for illegal move), NOT 41 or 42.
    assert(game.getCodeResponse() != 41 && game.getCodeResponse() != 42);

    const Board& board = game.currentBoard();
    // The King should still be on e1 (its original square).
    Piece* king = board.getPiece(7, 4);
    assert(king != nullptr && king->getSymbol() == 'k');

    // The Rook should still be on h1.
    Piece* rook = board.getPiece(7, 7);
    assert(rook != nullptr && rook->getSymbol() == 'r');

    std::cout << "\n✅ SUCCESS: Illegal castling move was correctly rejected." << std::endl;
}

int main() {
    try {
        test_legal_kingside_castling();
        test_illegal_castling_after_king_moved();
    } catch (const std::exception& e) {
        std::cerr << "❌ FAILURE: Test threw an exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ FAILURE: Test threw an unknown exception." << std::endl;
        return 1;
    }
    return 0;
}