#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>

class Knight : public Piece
{
public:
    Knight(char PieceColor);
    ~Knight();
private:
    virtual char GetPiece() {
        return 'N';
    }
    bool isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]);
};

#endif
