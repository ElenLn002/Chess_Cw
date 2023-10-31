#include "Piece.hpp"
#include "Rook.hpp"

Rook::Rook(char PieceColor) : Piece(PieceColor) {}
Rook::~Rook() {}
bool Rook::isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]) {
    if (SrcRow == DestRow) {
        // Make sure that all invervening squares are empty
        int ColArrow = (DestCol - SrcCol > 0) ? 1 : -1;
        for (int CheckCol = SrcCol + ColArrow; CheckCol != DestCol; CheckCol += ColArrow) {
            if (GameBoard[SrcRow][CheckCol] != 0) {
                return false;
            }
        }
        return true;
    }
    else if (DestCol == SrcCol) {
        // Make sure that all invervening squares are empty
        int RowArrow = (DestRow - SrcRow > 0) ? 1 : -1;
        for (int CheckRow = SrcRow + RowArrow; CheckRow != DestRow; CheckRow = CheckRow + RowArrow) {
            if (GameBoard[CheckRow][SrcCol] != 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}

