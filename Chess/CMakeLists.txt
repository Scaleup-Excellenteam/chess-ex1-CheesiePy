cmake_minimum_required(VERSION 3.15)

project(Chess)

# Set the C++ standard
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif ()

# --- 1. Define a library for the core game logic ---
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
target_include_directories(ChessLogic PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# --- 3. Define the main game executable ---
add_executable(Chess
    src/main.cpp
)
target_link_libraries(Chess PRIVATE ChessLogic)

# --- 4. Define the checkmate test executable ---
add_executable(run_tests
    ../tests/checkmate_test.cpp
)
target_link_libraries(run_tests PRIVATE ChessLogic)

# --- 5. Define the 'check' test executable ---
add_executable(run_check_test
    ../tests/check_test.cpp
)
target_link_libraries(run_check_test PRIVATE ChessLogic)

# --- 6. Define the castling test executable ---
add_executable(run_castling_test
    ../tests/castling_test.cpp
)
target_link_libraries(run_castling_test PRIVATE ChessLogic)


# Explicitly tell each test target where to find the headers.
target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(run_check_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(run_castling_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)