#include "Piece.hpp"
#include "Pawn.hpp"
Pawn::Pawn(char PieceColor) : Piece(PieceColor) {}
Pawn::~Pawn() {};
bool Pawn::isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]) {
    Piece* Dest = GameBoard[DestRow][DestCol];
    if (Dest == 0) {
        // Destination square is unoccupied
        if (SrcCol == DestCol) {
            if (GetColor() == 'W' && SrcRow == 1 && DestRow == SrcRow + 2) {
                return true;
            }
            else {
                if (SrcRow == 6 && DestRow == SrcRow - 2) {
                    return true;
                }
            }
            if (GetColor() == 'W') {
                if (DestRow == SrcRow + 1) {
                    return true;
                }
            }
            else {
                if (DestRow == SrcRow - 1) {
                    return true;
                }
            }
        }
    }
    else {
        // Dest holds piece of opposite color
        if ((SrcCol == DestCol + 1) || (SrcCol == DestCol - 1)) {
            if (GetColor() == 'W') {
                if (DestRow == SrcRow + 1) {
                    return true;
                }
            }
            else {
                if (DestRow == SrcRow - 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

