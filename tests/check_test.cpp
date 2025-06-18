#include "GameManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

void run_check_test() {
    std::cout << "--- Running C++ Test: Scholar's Mate 'Check' Condition ---" << std::endl;
    GameManager game;

    // Standard algebraic notation for Scholar's Mate opening
    const std::vector<std::string> moves = {
        "e2e4",
        "e7e5",
        "f1c4",
        "b8c6",
        "d1h5",
        "g8f6",
        "h5f7" 
    };

    for (const auto& move_str : moves) {
        std::cout << "Applying move: " << move_str
                  << " for " << (game.whiteToMove() ? "White" : "Black") << std::endl;
        game.makeMove(move_str);
    }

    std::cout << "Final move applied. Verifying 'check' state..." << std::endl;

    assert(game.getCodeResponse() == 41);
    assert(game.isCheck() == true);
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