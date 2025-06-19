Chess/                        ← root directory
├── include/                  ← public headers
│   ├── Chess.h               ← ascii-UI & I/O APIs
│   ├── GameManager.h         ← game-flow controller interface
│   ├── Board.h               ← board model & accessors
│   ├── Piece.h               ← abstract Piece base class
│   ├── Rook.h                ← rook movement rule definitions
│   ├── Knight.h              ← knight movement rule definitions
│   ├── Bishop.h              ← bishop movement rule definitions
│   ├── Queen.h               ← queen movement rule definitions
│   ├── King.h                ← king movement rule definitions & castling flags
│   ├── Pawn.h                ← pawn movement rule definitions & promotion
│   └── Utils/                ← reusable utilities
│       └── PriorityQueue.h   ← templated priority queue for move-scoring & other algorithms
├── src/                      ← implementation
│   ├── main.cpp              ← entry point; initializes and runs the game loop
│   ├── Chess.cpp             ← ASCII-board rendering & user input parsing
│   ├── GameManager.cpp       ← implements GameManager logic & rule enforcement
│   ├── Board.cpp             ← implements Board storage & piece manipulation
│   ├── Pieces/               ← piece-specific logic
│   │   ├── Rook.cpp          ← rook move validation & path-checking
│   │   ├── Knight.cpp        ← L-shaped move validation
│   │   ├── Bishop.cpp        ← diagonal move validation & path-checking
│   │   ├── Queen.cpp         ← combined rook/bishop move logic
│   │   ├── King.cpp          ← one-square moves, check detection & castling
│   └── └── Pawn.cpp          ← forward moves, captures, en passant & promotion
└── CMakeLists.txt            ← build configuration & target definitions
