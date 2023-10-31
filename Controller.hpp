#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>

#include "Piece.hpp"
#include "Pawn.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "BoardChecks.hpp"

class Controller
{
public:
    BoardChecks chessGameBoard;
    Piece* chessPiece[8][8];
    char PlayerTurn;
    char choice;

public:
    Controller();
    ~Controller();
    void Menu();
    void Start();
    void GetNextMove(Piece* GameBoard[8][8]);
    void MoveTurn();
    bool IsGameOver();

};

#endif
