#include "GameManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

/**
 * @brief Runs a sequence of moves to put a king in check and verifies the state.
 *
 * This test uses the Scholar's Mate opening to create a "check" scenario
 * and asserts that the game logic correctly identifies it without calling it a checkmate.
 */
void run_check_test() {
    std::cout << "--- Running C++ Test: Scholar's Mate 'Check' Condition ---" << std::endl;
    GameManager game;

    // A sequence leading to a check (but not checkmate)
    // The final move, d8b6 (Queen to f7), delivers the check.
    const std::vector<std::string> moves = {
        "g5e5",  // White: e2-e4
        "B5D5",  // Black: e7-e5
        "h6e3",  // White: Bishop f1-c4
        "A2Cc3", // Black: Knight b8-c6
        "h4d8",  // White: Queen d1-h5
        "A7C6",  // Black: Knight g8-f6
        "d8b6"   // White: Queen h5-f7 (CHECK!)
    };

    for (const auto& move_str : moves) {
        std::cout << "Applying move: " << move_str
                  << " for " << (game.whiteToMove() ? "White" : "Black") << std::endl;
        game.makeMove(move_str);
    }

    std::cout << "Final move applied. Verifying 'check' state..." << std::endl;

    // 1. After the last move, the game should report code 41 for "check".
    assert(game.getCodeResponse() == 41);

    // 2. The game state should be "in check".
    assert(game.isCheck() == true);

    // 3. Crucially, it should NOT be checkmate.
    assert(game.isCheckmate() == false);

    std::cout << "\n✅ SUCCESS: 'Check' condition correctly detected (and not mistaken for checkmate)." << std::endl;
}

int main() {
    try {
        run_check_test();
    } catch (const std::exception& e) {
        std::cerr << "❌ FAILURE: Test threw an exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ FAILURE: Test threw an unknown exception." << std::endl;
        return 1;
    }
    return 0;
}