#ifndef CHESS_UTILS_EXCEPTION_H
#define CHESS_UTILS_EXCEPTION_H

#include <exception>
#include <string>

namespace ChessException {

/**
 * base class for all chess-related errors
 */
class ChessError : public std::exception {
public:
    explicit ChessError(const std::string& msg) noexcept
        : message_(msg) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

/** board access errors */
class BoardException : public ChessError {
public:
    using ChessError::ChessError;
};

class OutOfBoundsException : public BoardException {
public:
    OutOfBoundsException(int r, int c) noexcept
        : BoardException("board indices out of bounds: (" + std::to_string(r) + "," + std::to_string(c) + ")") {}
};

class NoPieceException : public BoardException {
public:
    NoPieceException(int r, int c) noexcept
        : BoardException("no piece at: (" + std::to_string(r) + "," + std::to_string(c) + ")") {}
};

/** move-related errors */
class MoveException : public ChessError {
public:
    using ChessError::ChessError;
};

class InvalidMoveException : public MoveException {
public:
    explicit InvalidMoveException(const std::string& why) noexcept
        : MoveException("invalid move: " + why) {}
};

class NotYourTurnException : public MoveException {
public:
    NotYourTurnException() noexcept
        : MoveException("not your turn") {}
};

/** game state errors */
class GameLogicException : public ChessError {
public:
    using ChessError::ChessError;
};

class CheckmateException : public GameLogicException {
public:
    explicit CheckmateException(const std::string& winner) noexcept
        : GameLogicException("checkmate! winner: " + winner) {}
};

class StalemateException : public GameLogicException {
public:
    StalemateException() noexcept
        : GameLogicException("stalemate") {}
};

/** utility exceptions */
class UnderflowException : public ChessError {
public:
    UnderflowException() noexcept
        : ChessError("priority queue underflow") {}
};

} // namespace ChessException

#endif // CHESS_UTILS_EXCEPTION_H
