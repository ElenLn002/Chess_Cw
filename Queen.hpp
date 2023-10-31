#ifndef QUEEN_H
#define QUEEN_H


class Queen : public Piece
{
public:
    Queen(char PieceColor);
    ~Queen();
private:
    virtual char GetPiece() {
        return 'Q';
    }
    bool isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]);
};

#endif 
