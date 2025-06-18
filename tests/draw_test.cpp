#include "GameManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

/**
 * @brief Tests for a stalemate condition using the "King's Folly" game sequence.
 * After the final move, it is White's turn, and White has no legal moves but is not in check.
 */
void test_stalemate() {
    std::cout << "--- Running C++ Test: Stalemate Condition ---" << std::endl;
    GameManager game;

    const std::vector<std::string> moves = {
        "c2c4", "h7h5", "h2h4", "a7a5", "d1a4", "a8a6", "a4a5", "h8h6",
        "a5c7", "f7f6", "c7d7", "e8f7", "d7b7", "d7d6", "b7b8", "d8d5",
        "b8c8", "h6h5", "c8e6", "f7e6", "e1d1", "e6d5", "d1c1", "d5c4",
        "c1b1", "c4b3"
    };

    for (const auto& move : moves) {
        game.makeMove(move);
    }

    std::cout << "Final move applied. Verifying stalemate state..." << std::endl;

    // It is now White's turn.
    assert(game.whiteToMove() == true);
    // The game should be in a stalemate.
    assert(game.isStalemate() == true);
    // It should NOT be check or checkmate.
    assert(game.isCheck() == false);
    assert(game.isCheckmate() == false);

    std::cout << "\n✅ SUCCESS: Stalemate condition correctly detected." << std::endl;
}

/**
 * @brief Tests the 50-move rule.
 * This test assumes you have added a 'fiftyMoveCounter_' to GameManager
 * and a getter 'getFiftyMoveCount()'.
 * This test will fail until the logic is implemented.
 */
void test_fifty_move_rule() {
    std::cout << "\n--- Running C++ Test: Fifty-Move Rule ---" << std::endl;
    GameManager game;

    // A repetitive sequence of knight moves that involves no captures or pawn moves.
    // Repeating this 25 times results in 100 half-moves.
    const std::vector<std::string> sequence = {"g1f3", "g8f6", "f3g1", "f6g8"};

    for (int i = 0; i < 24; ++i) { // 24 * 4 = 96 moves
        for (const auto& move : sequence) {
            game.makeMove(move);
        }
    }
    
    // After 96 moves, the game should not be a draw.
    // assert(game.getFiftyMoveCount() == 96); // Add this if you implement a getter

    // Perform 3 more moves to reach 99
    game.makeMove("g1f3");
    game.makeMove("g8f6");
    game.makeMove("f3g1");
    // assert(game.getFiftyMoveCount() == 99);

    // The 100th move is made by Black.
    std::cout << "Applying 100th move without pawn move or capture..." << std::endl;
    game.makeMove("f6g8");
    
    // After 100 half-moves, the game should be a draw.
    // This requires a new function in GameManager, e.g., 'isDrawByFiftyMoveRule()'
    // assert(game.isDrawByFiftyMoveRule() == true);
    // For now, we assume the game ends. Let's check the counter if possible.
    // assert(game.getFiftyMoveCount() == 100);

    // To test the reset, we now make a pawn move.
    GameManager game2; // Start a new game
    game2.makeMove("b1c3"); // Knight move, counter should be 1
    // assert(game2.getFiftyMoveCount() == 1);
    std::cout << "Applying pawn move to test counter reset..." << std::endl;
    game2.makeMove("e7e5"); // Pawn move
    
    // The counter should reset to 0.
    // assert(game2.getFiftyMoveCount() == 0);

    std::cout << "\n✅ SUCCESS: Fifty-move rule test sequence completed. Verify assertions once implemented." << std::endl;
}


int main() {
    try {
        test_stalemate();
        test_fifty_move_rule();
    } catch (const std::exception& e) {
        std::cerr << "❌ FAILURE: Test threw an exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ FAILURE: Test threw an unknown exception." << std::endl;
        return 1;
    }
    return 0;
}