#ifndef PAWN_H
#define PAWN_H
#include <iostream>
class Pawn : public Piece
{
public:
    Pawn(char PieceColor);
    ~Pawn();
private:
    virtual char GetPiece() {
        return 'P';
    }
    bool isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]);
};
#endif
