#ifndef BOARDCHECKS_H
#define BOARDCHECKS_H
#include <iostream>

#include "Piece.hpp"
#include "Pawn.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"

class BoardChecks
{
public:
    Piece* GameBoard[8][8];

public:
    BoardChecks();
    ~BoardChecks();
    void PrintBoard();
    //void PrintPossibleMoves(int SrcRow, int SrcCol, Piece* GameBoard[8][8]);
    bool IsInCheck(char PieceColor);
    bool CanMove(char PieceColor);


};

#endif
