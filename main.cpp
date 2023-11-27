#include "GameController.hpp"


int main() {
    GameController& gameController = GameController::getInstance();
    gameController.startGame();

    return 0;
}


