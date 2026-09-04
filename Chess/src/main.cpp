#include <iostream>
#include <string>
#include <vector>
#include <chrono>   // Required for timing the benchmark
#include <memory>   // Required for std::unique_ptr

#include "Chess.h"
#include "GameManager.h"
#include "AI/BestMoveFinder.h"
#include "Utils/ThreadPool.h"

// Forward-declaration for our new benchmark function
void runBenchmark(int numThreads, int searchDepth);

// A placeholder for a single-threaded version of your findBestMoves function.
// You will need to implement this logic based on your AI.
// This version should NOT use a thread pool.
std::vector<MoveScorePair> findBestMoves_single_threaded(const Board& board, bool isWhite, int limit, int depth)
{
    // This is a placeholder implementation.
    // You should copy your sequential AI logic here.
    // This is the version that will be used when numThreads == 0.
    Board root = board;
    std::vector<MoveScorePair> out;
    // ... (Your sequential move generation and minimax calls go here)
    return out;
}


int main()
{
    int searchDepth;
    int gameMode;

    // Per the PDF requirements, get user input for search depth and game mode
    std::cout << "Enter search depth (e.g., 3 or 4): ";
    std::cin >> searchDepth;

    std::cout << "Select mode (1 for Interactive, 2 for Benchmark): ";
    std::cin >> gameMode;

    if (gameMode == 1)
    {
        // The original interactive game loop
        std::cout << "Starting interactive game..." << std::endl;
        Chess game; // Uses the default board setup
        std::string res = game.getInput();

        while (res != "exit" && res != "quit")
        {
            int codeResponse = game.validateMoveViaManager(res);
            game.setCodeResponse(codeResponse);
            res = game.getInput();
        }
        std::cout << std::endl << "Exiting." << std::endl;
    }
    else if (gameMode == 2)
    {
        // The new benchmark mode
        std::cout << "\n--- Running Benchmark (8 moves per test) ---" << std::endl;
        
        // Run the benchmark for each thread count required by the PDF
        runBenchmark(0, searchDepth);  // Special case for single-threaded baseline
        runBenchmark(2, searchDepth);
        runBenchmark(4, searchDepth);
        runBenchmark(8, searchDepth);

        std::cout << "\nBenchmark complete. Please record these results in your README.md" << std::endl;
    }
    else
    {
        std::cout << "Invalid mode selected." << std::endl;
    }

    return 0;
}

/**
 * @brief Runs an automatic 8-move game to measure the performance of the AI.
 * @param numThreads The number of threads to use in the thread pool. 0 means single-threaded.
 * @param searchDepth The search depth for the minimax algorithm.
 */
void runBenchmark(int numThreads, int searchDepth)
{
    std::cout << "\n------------------------------------------\n";
    std::cout << "--- Testing with " << numThreads << " threads and depth " << searchDepth << " ---" << std::endl;
    std::cout << "------------------------------------------\n";

    GameManager game; // Create a fresh game state for the test
    long long totalDuration_ms = 0;
    const int numMovesToPlay = 8; // The PDF specifies an 8-move automatic game

    for (int i = 0; i < numMovesToPlay; ++i)
    {
        const bool isWhiteTurn = game.whiteToMove();
        std::cout << "Move " << i + 1 << " (" << (isWhiteTurn ? "White" : "Black") << "): ";

        // Start the timer
        const auto startTime = std::chrono::high_resolution_clock::now();

        std::vector<MoveScorePair> bestMoves;

        if (numThreads == 0)
        {
            // For 0 threads, run the sequential version of the algorithm
            bestMoves = findBestMoves_single_threaded(game.currentBoard(), isWhiteTurn, 1, searchDepth);
        }
        else
        {
            // For 2, 4, or 8 threads, use your multithreaded function
            ThreadPool pool(numThreads);
            // NOTE: You will need to adapt your findBestMoves function to accept the pool and depth
            // For example: bestMoves = AI::findBestMoves(game.currentBoard(), isWhiteTurn, 1, pool, searchDepth);

            // Using the user-provided code structure as a base:
            // This assumes findBestMoves is refactored to take a pool and depth.
             bestMoves = AI::findBestMoves(game.currentBoard(), isWhiteTurn, 1);
        }

        // Stop the timer
        const auto endTime = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        
        totalDuration_ms += duration;
        

        if (bestMoves.empty())
        {
            std::cout << "Game over (Checkmate or Stalemate)." << std::endl;
            break;
        }

        // Print results for the current move
        std::cout << bestMoves[0].toString() << " | Time: " << duration << "ms" << std::endl;

        // Automatically play the best move to advance the game state
        const CMove move = bestMoves[0].move;
        game.makeMove(move.srcRow, move.srcCol, move.destRow, move.destCol);
    }

    std::cout << "------------------------------------------\n";
    std::cout << "Average time per move: " << totalDuration_ms / static_cast<double>(numMovesToPlay) << "ms\n";
    std::cout << "------------------------------------------\n";
}