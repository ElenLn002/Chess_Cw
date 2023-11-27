#include "GameController.hpp"

GameController::GameController() : isGameOver(false) {}

void GameController::printBoard() {
    std::cout << "  a b c d e f g h\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << BOARD_SIZE - i << " ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (gameBoard.board[i][j]) {
                std::cout << gameBoard.board[i][j]->getPieceType() << " ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << BOARD_SIZE - i << "\n";
    }
    std::cout << "  a b c d e f g h\n";
}

void GameController::getUserInput(Position& src, Position& dest) {
    std::string input;

    std::cout << "Enter source position (e.g., 'a2'): ";
    std::cin >> input;

    if (input.size() != 2 || !isalpha(input[0]) || !isdigit(input[1])) {
        std::cout << "Invalid input format. Please enter a valid position." << std::endl;
        getUserInput(src, dest);
        return;
    }

    char srcCol = input[0];
    int srcRow = input[1] - '0';
    src.col = srcCol - 'a';
    src.row = BOARD_SIZE - srcRow; 

    std::cout << "Source position: " << srcCol << srcRow << " -> Position: " << src.row << ", " << src.col << std::endl;

    std::cout << "Enter destination position (e.g., 'b4'): ";
    std::cin >> input;

    if (input.size() != 2 || !isalpha(input[0]) || !isdigit(input[1])) {
        std::cout << "Invalid input format. Please enter a valid position." << std::endl;
        getUserInput(src, dest);
        return;
    }
    char destCol = input[0];
    int destRow = input[1] - '0'; 
    dest.col = destCol - 'a';
    dest.row = BOARD_SIZE - destRow; 

    std::cout << "Destination position: " << destCol << destRow << " -> Position: " << dest.row << ", " << dest.col << std::endl;
}

void GameController::playGame() {
    while (!isGameOver) {
        printBoard();
        Position src, dest;
        getUserInput(src, dest);
        bool moveSuccess = gameLogic.makeMove(src, dest, gameBoard.board);
        if (!moveSuccess) {
            std::cout << "Invalid move. Please try again." << std::endl;
            continue;
        }
        isGameOver = gameLogic.isCheckmate(gameBoard.board, gameLogic.currentPlayer);
        if (isGameOver) {
            std::cout << "Checkmate! Game over." << std::endl;
            break;
        }
        if (gameLogic.isStalemate(gameBoard.board, gameLogic.currentPlayer)) {
            std::cout << "Stalemate! Game over." << std::endl;
            break;
        }
        gameLogic.switchTurn();
    }
    printBoard();
}


void GameController::startGame() {
    isGameOver = false;
    while (!isGameOver) {
        printBoard();
        Position src, dest;
        getUserInput(src, dest);
        bool moveSuccess = gameLogic.makeMove(src, dest, gameBoard.board);
        if (!moveSuccess) {
            std::cout << "Invalid move. Please try again." << std::endl;
            continue;
        }
        isGameOver = gameLogic.isCheckmate(gameBoard.board, gameLogic.currentPlayer);
        if (isGameOver) {
            std::cout << "Checkmate! Game over." << std::endl;
            break;
        }
        if (gameLogic.isStalemate(gameBoard.board, gameLogic.currentPlayer)) {
            std::cout << "Stalemate! Game over." << std::endl;
            break;
        }
        gameLogic.switchTurn();
    }
    printBoard();
}