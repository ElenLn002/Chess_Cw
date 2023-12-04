#include "Includes.hpp"
#include "QtIncludes.hpp"
#include "Definitions.hpp"
#include "BoardManager.hpp"
#include "ChessBoardWidget.hpp"
#include "GameLogic.cpp"

class Controller : public QObject {
    Q_OBJECT
private:
    ChessBoardWidget* chessBoard;
    BoardManager boardManager;
    PieceColour playerTurn;
    GameLogic gameLogic;
public:
    Controller() : boardManager(), gameLogic(), playerTurn(PieceColour::White) {}

    void changePlayerTurn() {
        playerTurn = (playerTurn == PieceColour::White) ? PieceColour::Black : PieceColour::White;
    }
    bool isGameOver() {
    bool currentPlayerCanMove = gameLogic.canMove(playerTurn, boardManager);
    bool opponentCanMove = gameLogic.canMove((playerTurn == PieceColour::White) ? PieceColour::Black : PieceColour::White, boardManager);
        if (!currentPlayerCanMove && !opponentCanMove) {
            if (!gameLogic.isInCheck(playerTurn, boardManager)) {
                std::cout << "Stalemate!" << std::endl;
                return true; 
            }
        }
        return false; 
    }
    void startGame() {

    }

};
