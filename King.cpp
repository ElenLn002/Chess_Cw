#include "Piece.hpp"
#include "King.hpp"
King::King(char PieceColor) : Piece(PieceColor) {}
King::~King() {}
bool King::isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]) {
    int kingMoveRow = DestRow - SrcRow;
    int kingMoveCol = DestCol - SrcCol;
    if (((kingMoveRow >= -1) && (kingMoveRow <= 1)) &&
        ((kingMoveCol >= -1) && (kingMoveCol <= 1)))
    {
        return true;
    }
    return false;
}
