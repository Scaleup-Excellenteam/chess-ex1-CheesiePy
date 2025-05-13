Chess/                        ← root directory
├── include/                  ← public headers
│   ├── Chess.h               ← ascii-ui & I/O APIs
│   ├── GameManager.h         ← game-flow controller
│   ├── Board.h               ← board model
│   ├── Piece.h               ← piece abstraction
│   ├── Rook.h                ← rook movement rules
│   ├── Knight.h              ← knight movement rules
│   ├── Bishop.h              ← bishop movement rules
│   ├── Queen.h               ← queen movement rules
│   ├── King.h                ← king movement rules
│   └── Pawn.h                ← pawn movement rules
├── src/                      ← implementation
│   ├── main.cpp              ← entry point; invokes UI & game loop
│   ├── Chess.cpp             ← ascii-board rendering & input parsing
│   ├── GameManager.cpp       ← implements GameManager APIs
│   ├── Board.cpp             ← implements Board storage & access
│   └── Pieces/               ← piece-specific logic
│       ├── Rook.cpp
│       ├── Knight.cpp
│       ├── Bishop.cpp
│       ├── Queen.cpp
│       ├── King.cpp
│       └── Pawn.cpp
└── CMakeLists.txt            ← build configuration
