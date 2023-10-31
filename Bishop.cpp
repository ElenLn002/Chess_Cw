#include "Piece.hpp"
#include "Bishop.hpp"
Bishop::Bishop(char PieceColor) : Piece(PieceColor) {}
Bishop::~Bishop() {}
bool Bishop::isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]) {
    if ((DestCol - SrcCol == DestRow - SrcRow) || (DestCol - SrcCol == SrcRow - DestRow)) {
        // Make sure that all invervening squares are empty
        int RowArrow = (DestRow - SrcRow > 0) ? 1 : -1;
        int ColArrow = (DestCol - SrcCol > 0) ? 1 : -1;
        int CheckRow;
        int CheckCol;
        for (CheckRow = SrcRow + RowArrow, CheckCol = SrcCol + ColArrow;
            CheckRow != DestRow;// CheckCol != DestCol;
            CheckRow += RowArrow, CheckCol += ColArrow)
        {
            if (GameBoard[CheckRow][CheckCol] != 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}
