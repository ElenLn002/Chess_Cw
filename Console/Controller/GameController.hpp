#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include "Board.hpp"
#include "GameLogic.hpp"


class GameController {
public:
    static GameController& getInstance() {
        static GameController instance; // Singleton instance
        return instance;
    }

    GameController(const GameController&) = delete; // Delete copy constructor
    GameController& operator=(const GameController&) = delete;

    void startGame();
    void printBoard();
    void getUserInput(Position& src, Position& dest);
    void playGame();

private:
    GameController();
    Board gameBoard;
    GameLogic gameLogic;
    bool isGameOver;
};

#endif // !GAMECONTROLLER_HPP
