cmake_minimum_required(VERSION 3.15)

project(Chess)

# Set the C++ standard (your existing logic is perfect)
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Windows-specific compile options
if (MSVC)
    add_compile_options(/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif ()


# --- 1. Define a library for the core game logic ---
# This includes all source files EXCEPT those with a main() function.
# We also include Chess.cpp here as it contains the UI logic used by the main game.
add_library(ChessLogic
    src/Board.cpp
    src/GameManager.cpp
    src/Chess.cpp 
    src/AI/BestMoveFinder.cpp
    src/Utils/ThreadPool.cpp
    src/Utils/ThreadPoolSingleton.cpp
    src/Pieces/Rook.cpp
    src/Pieces/Queen.cpp
    src/Pieces/Bishop.cpp
    src/Pieces/Knight.cpp
    src/Pieces/Pawn.cpp
    src/Pieces/King.cpp
)

# --- 2. Make the library's headers available ---
# This tells any target that uses ChessLogic where to find the header files.
target_include_directories(ChessLogic PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# --- 3. Define the main game executable ---
# It now only contains the main entry point file.
add_executable(Chess
    src/main.cpp
)
# Link the main game against the logic library.
target_link_libraries(Chess PRIVATE ChessLogic)


# --- 4. Define the new test executable ---
# The path to the test file is relative to this CMakeLists.txt
# (../tests/ means "go up one directory from 'Chess/' and then into 'tests/')
add_executable(run_tests
    ../tests/checkmate_test.cpp
)
# Link the test against the logic library as well, so it can use GameManager, etc.
target_link_libraries(run_tests PRIVATE ChessLogic)