#ifndef KING_H
#define KING_H
#include <iostream>

class King : public Piece
{
public:
    King(char PieceColor);
    ~King();
private:
    virtual char GetPiece() {
        return 'K';
    }
    bool isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]);
};

#endif
