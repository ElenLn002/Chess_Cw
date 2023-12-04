#ifndef GAME_LOGIC
#define GAME_LOGIC

#include "Includes.hpp"
#include"Const.hpp"
#include "Piece.hpp"

class GameLogic {
public:
    GameLogic();
    void switchTurn();
    bool isInCheck(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour);
    bool validateMove(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);
    bool isCheckmate(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour);
    bool isStalemate(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour);
    //bool isDraw(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour);
    bool makeMove(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);
    PieceColour currentPlayer;
};


#endif // !GAME_LOGIC
