#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <vector>
#include <memory>

class Board;
class Piece;

class GameManager
{
private:
    std::unique_ptr<Board> board;
    std::vector<Piece*> pieces;
    bool isWhiteTurn_ = true;
    int codeResponse;
    int fiftyMoveCounter_ = 0;

public:
    GameManager();
    ~GameManager();

    void initGame();
    void setCodeResponse(int code);
    int getCodeResponse() const;
    bool isCheck() const;

    void makeMove(const std::string& move);
    bool makeMove(int srcRow, int srcCol, int destRow, int destCol);
    int validateMove(const std::string& mv) const;

    bool isCheckmate() const;
    bool isStalemate() const;

    const Board& currentBoard() const;
    bool whiteToMove() const;

    int getFiftyMoveCounter() const { return fiftyMoveCounter_; }
    void resetFiftyMoveCounter() { fiftyMoveCounter_ = 0; }
    void incrementFiftyMoveCounter() { ++fiftyMoveCounter_; }
    bool isFiftyMoveDraw() const { return fiftyMoveCounter_ >= 100; }
};

#endif // GAMEMANAGER_H