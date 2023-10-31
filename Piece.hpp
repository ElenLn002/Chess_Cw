#ifndef PIECE_H
#define PIECE_H
#include <iostream>
class Piece
{
protected:
    virtual bool isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]) = 0;
    char chessPieceColor;

public:
    Piece(char PieceColor);
    ~Piece();
    virtual char GetPiece() = 0;
    char GetColor();
    bool isMoveValid(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]);
    //void PrintPossibleMoves(int SrcRow, int SrcCol, int Row, int Col, Piece* GameBoard[8][8]);

};

#endif
