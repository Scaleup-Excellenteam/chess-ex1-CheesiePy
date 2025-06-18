#include "GameManager.h" // Includes all necessary game logic headers
#include <iostream>
#include <vector>
#include <string>
#include <cassert> // For asserting test conditions

/**
 * @brief Runs a sequence of moves for "Fool's Mate" and asserts the outcome.
 *
 * This test uses the game's unconventional coordinate system (Letter=Row, Number=Col)
 * to verify that the checkmate rule is correctly implemented.
 */
void run_fools_mate_test() {
    std::cout << "--- Running C++ Test: Fool's Mate ---" << std::endl;
    GameManager game;

    // Standard Fool's Mate: 1. f3 e5   2. g4 Qh4#
    // Translated to this game's coordinates:
    // 1. White pawn (g6->f6), Black pawn (b5->d5)
    // 2. White pawn (g7->e7), Black Queen (a4->e8) for checkmate
    const std::vector<std::string> moves = {
        "f2f3",
        "E7E5",
        "g2g4",
        "D8H4"
    };

    for (const auto& move_str : moves) {
        std::cout << "Applying move: " << move_str
                  << " for " << (game.whiteToMove() ? "White" : "Black") << std::endl;

        // The makeMove function validates the move and switches the turn
        game.makeMove(move_str);

        // A legal move returns code 41 (check) or 42 (legal). Assert this.
        int response = game.getCodeResponse();
        assert(response == 41 || response == 42);
    }

    std::cout << "Final move applied. Verifying checkmate state..." << std::endl;

    // After black's final move, it is now white's turn.
    // White should be in checkmate and have no legal moves.
    assert(game.whiteToMove() == true);
    assert(game.isCheckmate() == true);

    std::cout << "\n✅ SUCCESS: Checkmate correctly detected!" << std::endl;
}

int main() {
    try {
        run_fools_mate_test();
    } catch (const std::exception& e) {
        std::cerr << "❌ FAILURE: Test threw an exception: " << e.what() << std::endl;
        return 1; // Exit with an error code
    } catch (...) {
        std::cerr << "❌ FAILURE: Test threw an unknown exception." << std::endl;
        return 1; // Exit with an error code
    }
    return 0; // Success
}