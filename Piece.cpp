#include "Piece.hpp"
Piece::Piece(char PieceColor) : chessPieceColor(PieceColor) {}
Piece::~Piece() {};
char Piece:: GetColor() {
    return chessPieceColor;
}
bool Piece::isMoveValid(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]) {
    Piece* Dest = GameBoard[DestRow][DestCol];
    if ((Dest == 0) || (chessPieceColor != Dest->GetColor())) {
        return isMoveLegal(SrcRow, SrcCol, DestRow, DestCol, GameBoard);
    }
    return false;
}
