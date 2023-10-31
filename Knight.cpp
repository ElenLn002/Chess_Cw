#include "Piece.hpp"
#include "Knight.hpp"

Knight:: Knight(char PieceColor) : Piece(PieceColor) {}
Knight::~Knight() {}
bool Knight::isMoveLegal(int SrcRow, int SrcCol, int DestRow, int DestCol, Piece* GameBoard[8][8]) {
    // Destination square is unoccupied or occupied by opposite color
    if ((SrcCol == DestCol + 1) || (SrcCol == DestCol - 1)) {
        if ((SrcRow == DestRow + 2) || (SrcRow == DestRow - 2)) {
            return true;
        }
    }
    if ((SrcCol == DestCol + 2) || (SrcCol == DestCol - 2)) {
        if ((SrcRow == DestRow + 1) || (SrcRow == DestRow - 1)) {
            return true;
        }
    }
    return false;
}
