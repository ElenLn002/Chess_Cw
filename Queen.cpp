#include "Piece.hpp"
#include "Queen.hpp"
Queen::Queen(char PieceColor) : Piece(PieceColor) {}
Queen::~Queen() {}
bool Queen::isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]) {
    if (SrcRow == DestRow) {
        // Make sure that all invervening squares are empty
        int ColArrow = (DestCol - SrcCol > 0) ? 1 : -1;
        for (int CheckCol = SrcCol + ColArrow; CheckCol != DestCol; CheckCol = CheckCol + ColArrow) {
            if (GameBoard[SrcRow][CheckCol] != 0) {
                return false;
            }
        }
        return true;
    }
    else if (DestCol == SrcCol) {
        // Make sure that all invervening squares are empty
        int RowArrow = (DestRow - SrcRow > 0) ? 1 : -1;
        for (int CheckRow = SrcRow + RowArrow; CheckRow != DestRow; CheckRow += RowArrow) {
            if (GameBoard[CheckRow][SrcCol] != 0) {
                return false;
            }
        }
        return true;
    }
    else if ((DestCol - SrcCol == DestRow - SrcRow) || (DestCol - SrcCol == SrcRow - DestRow)) {
        // Make sure that all invervening squares are empty
        int RowArrow = (DestRow - SrcRow > 0) ? 1 : -1;
        int ColArrow = (DestCol - SrcCol > 0) ? 1 : -1;
        int CheckRow;
        int CheckCol;
        for (CheckRow = SrcRow + RowArrow, CheckCol = SrcCol + ColArrow;
            CheckRow != DestRow;
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

