
# C++ Multithreaded Chess AI 🤖

> A powerful command-line chess engine featuring a smart AI opponent that uses C++ multithreading to find the best move with incredible speed.

<div align="center">
    <img src="https://img.shields.io/badge/Language-C++-blue.svg" alt="Language C++">
    <img src="https://img.shields.io/badge/Build-CMake-green.svg" alt="Build CMake">
    <img src="https://img.shields.io/badge/CI-Passing-brightgreen" alt="CI Passing">
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License MIT">
</div>


-----

## 📚 Table of Contents

  * [🎯 Project Overview](https://www.google.com/search?q=%23-project-overview)
  * [🚀 Key Features](https://www.google.com/search?q=%23-key-features)
  * [🛠️ Environment Setup](https://www.google.com/search?q=%23%EF%B8%8F-environment-setup)
  * [⚙️ Build & Run Instructions](https://www.google.com/search?q=%23%EF%B8%8F-build--run-instructions)
  * [📁 Project Structure](https://www.google.com/search?q=%23-project-structure)
  * [🧠 Multithreading Architecture](https://www.google.com/search?q=%23-multithreading-architecture)
  * [📊 Benchmark Results](https://www.google.com/search?q=%23-benchmark-results)

-----

## 🎯 Project Overview

Welcome to a classic game of chess with a modern twist\! This project brings the timeless strategy game to your command line, powered by a C++ engine. It handles all game logic, from piece movement to validating complex states like check and checkmate.

The standout feature is the intelligent AI opponent. It doesn't just play random moves; it analyzes the board using the **minimax algorithm** and leverages a **custom multithreaded architecture** to find the optimal move, making for a challenging and responsive gameplay experience.

## 🚀 Key Features

  * ♟️ **Complete Chess Logic**: Implements all standard FIDE chess rules for piece movement, captures, and special moves.
  * 🤖 **Intelligent AI Opponent**: Features a game AI built on the minimax algorithm to evaluate board states and make strategic decisions.
  * ⚡ **High-Performance Multithreading**: The AI's move calculation is heavily parallelized using a custom thread pool, leveraging multi-core processors for a significant performance boost.
  * 🔒 **Thread-Safe by Design**: Employs `std::mutex` to protect shared data structures, ensuring that move results from different threads are collected safely and without race conditions.
  * 🕹️ **Dual Game Modes**: Includes a standard **Interactive Mode** for player-vs-AI gameplay and an automatic **Benchmark Mode** to measure the performance of the multithreaded engine.

## 🛠️ Environment Setup

This project is designed for a Linux-based environment (including WSL for Windows). Ensure you have the following tools installed:

  * `g++` (GNU C++ Compiler)
  * `cmake`
  * `make`

You can install these dependencies on an Ubuntu system with a single command:

```sh
sudo apt update
sudo apt install -y g++ cmake make
```

## ⚙️ Build & Run Instructions

Compiling and running the project is straightforward thanks to CMake. Open your terminal in the project's root directory and follow these steps:

you can try running this script
```sh
./run.sh
```

if its not working properly please let me know 
and try this:

```sh
# 1. Create a build directory to keep things clean
mkdir -p build

# 2. Navigate into the new directory
cd build

# 3. Configure the project using CMake
cmake ..
# if the build folder is in the same place as the Chess folder try 
cmake ../Chess/

# 4. Compile the source code into an executable
make

# 5. Run the game!
./Chess
```

> After running, the application will prompt you to enter the desired AI search depth and to choose between Interactive and Benchmark modes.

## 📁 Project Structure

The codebase is organized into a clean, modular architecture to separate concerns and improve maintainability.

```
Chess/
├── include/                  # Public headers for all classes
│   ├── AI/
│   ├── Pieces/
│   └── Utils/
├── src/                      # Source code implementation files
│   ├── AI/
│   ├── Pieces/
│   └── Utils/
├── CMakeLists.txt            # Root build configuration
└── ...
```

## 🧠 Multithreading Architecture

To improve the AI's response time, this project parallelizes the most computationally expensive task: finding the best move.

#### Work Division

When it's the AI's turn, the engine first generates all possible legal moves. These moves are then grouped into "buckets," where each bucket contains all the moves for a single piece.

#### Parallel Calculation

A **ThreadPool** dispatches each bucket to a different worker thread. The threads run in parallel, with each one executing the minimax algorithm on its assigned set of moves to calculate a score.

#### Synchronization

As threads complete their analysis, they push the results (the move and its score) into a shared, thread-safe priority queue. This custom queue, `SafeMovePQ`, uses a **`std::mutex`** to lock the data structure during write operations, preventing race conditions and ensuring data integrity. The main thread can then safely pull the highest-scoring move from the queue.

This architecture effectively turns a long, sequential process into a rapid, parallel search.

-----

## 📊 Benchmark Results

This section documents the performance of the `findBestMoves` function over an 8-move automatic game, using a search depth of **[Your Search Depth]**.

| Number of Threads | Average Time per Move (ms) |
| :---------------: | :------------------------: |
|         0 (Sequential)         |      **[Your Result]** |
|         2         |      **[Your Result]** |
|         4         |      **[Your Result]** |
|         8         |      **[Your Result]** |

### Analysis

```
▶️  Running build/Chess ...
Enter search depth (e.g., 3 or 4): 4
Select mode (1 for Interactive, 2 for Benchmark): 2

--- Running Benchmark (8 moves per test) ---

------------------------------------------
--- Testing with 0 threads and depth 4 ---
------------------------------------------
Move 1 (White): Game over (Checkmate or Stalemate).
------------------------------------------
Average time per move: 0ms
------------------------------------------

------------------------------------------
--- Testing with 2 threads and depth 4 ---
------------------------------------------
Move 1 (White): G1E1 (+0) | Time: 5ms
Move 2 (Black): B2D2 (+1) | Time: 4ms
Move 3 (White): E1D2 (+2) | Time: 5ms
Move 4 (Black): A2C1 (+3) | Time: 5ms
Move 5 (White): D2C1 (+4) | Time: 6ms
Move 6 (Black): A3B2 (+7) | Time: 3ms
Move 7 (White): C1B2 (+8) | Time: 4ms
Move 8 (Black): A4A3 (+15) | Time: 1ms
------------------------------------------
Average time per move: 4.125ms
------------------------------------------

------------------------------------------
--- Testing with 4 threads and depth 4 ---
------------------------------------------
Move 1 (White): G3E3 (+0) | Time: 1ms
Move 2 (Black): B2D2 (+1) | Time: 1ms
Move 3 (White): E3D2 (+1) | Time: 2ms
Move 4 (Black): A2C1 (+3) | Time: 1ms
Move 5 (White): D2C1 (+3) | Time: 2ms
Move 6 (Black): A3B2 (+7) | Time: 1ms
Move 7 (White): C1B2 (+7) | Time: 2ms
Move 8 (Black): A4A3 (+15) | Time: 1ms
------------------------------------------
Average time per move: 1.375ms
------------------------------------------

------------------------------------------
--- Testing with 8 threads and depth 4 ---
------------------------------------------
Move 1 (White): G2E2 (+0) | Time: 1ms
Move 2 (Black): B3D3 (+1) | Time: 1ms
Move 3 (White): E2D3 (+1) | Time: 1ms
Move 4 (Black): A4C2 (+9) | Time: 2ms
Move 5 (White): D3C2 (+9) | Time: 1ms
Move 6 (Black): B1C1 (+10) | Time: 1ms
Move 7 (White): H3F1 (+11) | Time: 1ms
Move 8 (Black): A1B1 (+15) | Time: 0ms
------------------------------------------
Average time per move: 1ms
------------------------------------------
```