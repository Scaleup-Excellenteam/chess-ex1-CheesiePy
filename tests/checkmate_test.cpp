#include "GameManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

void run_checkmate_test() {
    std::cout << "--- Running C++ Test: Fool's Mate ---" << std::endl;
    GameManager game;

    // Standard algebraic notation for Fool's Mate
    const std::vector<std::string> moves = {
        "f2f3",
        "e7e5",
        "g2g4",
        "d8h4"
    };

    for (const auto& move_str : moves) {
        std::cout << "Applying move: " << move_str
                  << " for " << (game.whiteToMove() ? "White" : "Black") << std::endl;
        game.makeMove(move_str);
    }

    std::cout << "Final move applied. Verifying checkmate state..." << std::endl;

    // After black's final move, it is white's turn.
    // White should be in checkmate.
    assert(game.whiteToMove() == true);
    assert(game.isCheckmate() == true);

    std::cout << "\n✅ SUCCESS: Checkmate correctly detected!" << std::endl;
}

int main() {
    try {
        run_checkmate_test();
    } catch (const std::exception& e) {
        std::cerr << "❌ FAILURE: Test threw an exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ FAILURE: Test threw an unknown exception." << std::endl;
        return 1;
    }
    return 0;
}