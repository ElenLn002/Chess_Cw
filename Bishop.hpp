#ifndef BISHOP_H
#define BISHOP_H
#include <iostream>

class Bishop : public Piece
{
public:
    Bishop(char PieceColor);
    ~Bishop();
private:
    virtual char GetPiece() {
        return 'B';
    }
    bool isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]);
};

#endif
