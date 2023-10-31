#ifndef ROOK_H
#define ROOK_H
#include <iostream>

class Rook : public Piece
{
public:
    Rook(char PieceColor);
    ~Rook();
private:
    virtual char GetPiece() {
        return 'R';
    }
    bool isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]);
};

#endif
