# C++ Multithreaded Chess AI 🤖

Welcome to a classic game of chess with a modern twist! This project brings the timeless strategy game to your command line, powered by a C++ engine. It handles all game logic, from piece movement to validating complex states like check and checkmate. The standout feature is the intelligent AI opponent that uses a multithreaded minimax algorithm to find the optimal move, making for a challenging and responsive gameplay experience.

<div align="center">
    <img src="https://img.shields.io/badge/Language-C++-blue.svg" alt="Language C++">
    <img src="https://img.shields.io/badge/Build-CMake-green.svg" alt="Build CMake">
    <img src="https://img.shields.io/badge/CI-Passing-brightgreen" alt="CI Passing">
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License MIT">
</div>

---

## 📚 Table of Contents

- [C++ Multithreaded Chess AI 🤖](#c-multithreaded-chess-ai-)
  - [📚 Table of Contents](#-table-of-contents)
  - [⚙️ How to Build \& Run](#️-how-to-build--run)
    - [Using the Run Script (Recommended)](#using-the-run-script-recommended)
    - [Manual Build \& Run](#manual-build--run)
  - [📁 Project Folder Structure](#-project-folder-structure)
  - [✨ Implemented Rules \& Features](#-implemented-rules--features)
    - [Chess Rules](#chess-rules)
    - [Application Features](#application-features)
  - [🧠 The Computer Player: AI Algorithm Explained](#-the-computer-player-ai-algorithm-explained)
    - [Minimax Algorithm](#minimax-algorithm)
    - [Alpha-Beta Pruning](#alpha-beta-pruning)
    - [Multithreading Architecture](#multithreading-architecture)
  - [🧪 Testing Strategy](#-testing-strategy)
  - [🧗 Biggest Challenge Faced](#-biggest-challenge-faced)
  - [🚀 Future Improvements](#-future-improvements)

---

## ⚙️ How to Build & Run

This project is designed for a Linux-based environment (including WSL for Windows). Ensure you have `g++`, `cmake`, and `make` installed.

### Using the Run Script (Recommended)

The easiest way to build and run the project is by using the provided shell script.

1.  **Give execute permissions to the script:**
    ```bash
    chmod +x run.sh
    ```
2.  **Run the game:**
    ```bash
    ./run.sh
    ```
    This will compile the project and start the main game in Player vs. Computer mode.

### Manual Build & Run

If you prefer to build the project manually, follow these steps:

1.  **Create a build directory:**
    ```bash
    mkdir -p build
    ```
2.  **Configure the project with CMake:**
    ```bash
    cmake -S Chess -B build
    ```
3.  **Compile the source code:**
    ```bash
    cmake --build build
    ```
4.  **Run the game executable:**
    ```bash
    ./build/Chess
    ```
After running, the application will prompt you to choose between Player vs Player, Player vs Computer, and Benchmark modes.

---

## 📁 Project Folder Structure

The codebase is organized into a clean, modular architecture to separate concerns and improve maintainability.

```
.
├── Chess/                  # Main project directory
│   ├── include/            # Public headers
│   │   ├── AI/             # AI-related headers
│   │   ├── Pieces/         # Piece class headers
│   │   └── Utils/          # Utility headers (ThreadPool, CMove, etc.)
│   ├── src/                # Source code implementation
│   │   ├── AI/             # AI algorithm implementation
│   │   ├── Pieces/         # Piece-specific logic
│   │   └── Utils/          # Utility implementations
│   ├── main.cpp            # Entry point for the application
│   └── CMakeLists.txt      # Build configuration for the game
├── docs/                   # Project documentation
│   └── ARCHITECTURE.md     # Detailed architecture overview
├── tests/                  # C++ test files
│   ├── checkmate_test.cpp
│   ├── castling_test.cpp
│   └── ...
├── run.sh                  # Script to build and run the game/tests
└── README.md               # This file
```

---

## ✨ Implemented Rules & Features

This project implements a robust set of chess rules and application features:

### Chess Rules
-   **Standard Piece Movement**: All pieces (Pawn, Rook, Knight, Bishop, Queen, King) move according to FIDE rules.
-   **Captures**: Pieces can capture opponent pieces.
-   **Check and Checkmate**: The game correctly identifies when a King is in check and detects checkmate to end the game.
-   **Stalemate**: The game recognizes a stalemate condition, resulting in a draw.
-   **Pawn Promotion**: Pawns are promoted to a Queen upon reaching the opposite end of the board. (Implicitly handled by replacing piece, user does not choose).
-   **Castling**: Both kingside and queenside castling are implemented, with checks to ensure it is a legal move (i.e., neither the King nor the Rook has moved, and the King is not in check).
-   **Fifty-Move Rule**: The game ends in a draw if 50 consecutive moves are made by each player without a capture or a pawn move.

### Application Features
-   **Player vs. Player Mode**: Two human players can play against each other.
-   **Player vs. Computer Mode**: A human can play against the multithreaded AI.
-   **ASCII-based UI**: A clean and functional command-line interface to display the board and interact with the game.
-   **Move Validation**: Robust input validation to ensure only legal moves are made.
-   **Benchmark Mode**: An automated mode to measure the performance of the AI with a varying number of threads (0, 2, 4, 8).

---

## 🧠 The Computer Player: AI Algorithm Explained

The AI opponent is the core of this project, designed to be a challenging adversary. Its decision-making is based on the **Minimax algorithm with Alpha-Beta Pruning**, and its performance is accelerated through **multithreading**.

### Minimax Algorithm
Minimax is a recursive algorithm used in two-player, zero-sum games. It explores a tree of all possible moves to a certain depth.
-   The **Maximizing** player (our AI) tries to find the move that leads to the highest possible score.
-   The **Minimizing** player (the opponent) is assumed to play optimally, always choosing the move that leads to the lowest score for the AI.

The score is determined by a static **evaluation function** (`evaluateBoard`), which calculates the material advantage on the board. Each piece has a value (Pawn=1, Knight/Bishop=3, Rook=5, Queen=9), and the function returns the difference between the total value of the AI's pieces and the opponent's pieces.

### Alpha-Beta Pruning
To make the search more efficient, we use **Alpha-Beta Pruning**. This optimization safely prunes large parts of the search tree that don't need to be explored because a better move has already been found.
-   **Alpha**: The best score found so far for the maximizing player.
-   **Beta**: The best score found so far for the minimizing player.

If the algorithm finds a move for the minimizing player that is worse than the maximizer's current best option (i.e., `beta <= alpha`), it stops exploring that branch.

### Multithreading Architecture
The most computationally expensive part of the AI is exploring the initial set of moves from the current board state. To speed this up, the work is parallelized:
1.  **Work Division**: All legal moves for the AI are generated. These moves are then grouped into "buckets," with each bucket containing the moves for a single piece.
2.  **Parallel Calculation**: A custom `ThreadPool` dispatches each bucket to a separate worker thread. Each thread independently runs the minimax algorithm on its assigned moves to calculate a score for each move.
3.  **Synchronization**: The results (move and score) from each thread are pushed into a shared, thread-safe priority queue (`SafeMovePQ`). This queue uses a `std::mutex` to ensure that results are added safely without race conditions. The main thread then retrieves the highest-scoring move from the queue.

This architecture significantly reduces the time the AI takes to decide on a move, creating a much more fluid gameplay experience.

---

## 🧪 Testing Strategy

The project's correctness is ensured through a suite of automated tests. These tests are written in C++ and are located in the `tests/` directory.

Each test executable focuses on a specific game mechanic:
-   `run_checkmate_test`: Verifies that the engine can correctly identify a checkmate situation (e.g., Fool's Mate).
-   `run_check_test`: Ensures the engine detects a 'check' without incorrectly flagging it as checkmate.
-   `run_castling_test`: Tests both legal and illegal castling scenarios to confirm the rules are enforced correctly.
-   `run_draw_test`: Validates draw conditions like stalemate and the fifty-move rule.
-   `run_pvc_test`: Simulates a basic Player vs. Computer turn sequence to ensure the interaction works as expected.

You can run all tests at once with the following command:
```bash
./run.sh all_tests
```

---

## 🧗 Biggest Challenge Faced

The most significant challenge during the development of this project was the **implementation of the AI agent**. This involved several complex, interconnected parts:

1.  **Correctly Implementing Minimax**: The recursive nature of the minimax algorithm, combined with the need to manage board state without making excessive copies, was difficult. The solution was to use an `applyMove` and `undoMove` pattern, which modifies a single board instance and then reverts it. This is efficient but requires careful state management to avoid bugs.

2.  **Integrating Alpha-Beta Pruning**: While the concept of alpha-beta pruning is straightforward, implementing it correctly within the recursive minimax function was tricky. Ensuring that the alpha and beta values were passed and updated correctly through the recursive calls was critical for the optimization to work effectively.

3.  **Designing the Multithreaded Architecture**: Parallelizing the AI's search was the most complex part. The main challenges were:
    -   **Thread Safety**: Ensuring that multiple threads could write their results to a shared data structure without causing race conditions or deadlocks. This was solved by creating a `SafeMovePQ` (thread-safe priority queue) protected by a `std::mutex`.
    -   **Work Distribution**: Deciding how to divide the work among threads. The chosen approach of creating "buckets" of moves for each piece provided a natural and effective way to distribute the load.
    -   **Synchronization**: Making the main thread wait for all worker threads to complete their calculations before determining the final best move. This was handled using `std::future` objects returned by the thread pool.

Overcoming these challenges required a deep understanding of recursion, game theory, and C++ concurrency primitives. The result is a powerful and efficient AI that makes this chess engine a formidable opponent.

---

## 🚀 Future Improvements

With more time, several improvements could be made to enhance the project:

-   **More Sophisticated Evaluation Function**: The current AI only evaluates material. A stronger AI would also consider:
    -   **Piece-Square Tables**: The value of a piece changes based on its position (e.g., a knight in the center is more valuable than one in a corner).
    -   **Board Control**: How many squares are attacked by each side.
    -   **Pawn Structure**: The arrangement of pawns can be a significant strategic factor.
-   **Opening and Endgame Databases**: To improve performance and play strength, the AI could use a database of standard openings and pre-calculated solutions for common endgame positions.
-   **Graphical User Interface (GUI)**: A simple graphical interface (using a library like SFML or Qt) would make the game more accessible and visually appealing than the current ASCII UI.
-   **Network Multiplayer**: Implement networking capabilities to allow two players to compete over the internet.
-   **Move History and Replay**: Allow players to view a history of the moves made and replay the game from any point.
-   **Save/Load Game Functionality**: Implement the ability to save the current game state to a file and load it later. This would allow players to pause and resume games at their convenience, and also enable sharing interesting positions or puzzles.


