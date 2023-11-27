#include "Bishop.hpp"

Bishop::Bishop(PieceColour colour) : Piece(colour), colour(colour) {}

bool Bishop::move(Position src, Position dest) {
    if (abs(src.row - dest.row) == abs(src.col - dest.col)) {
        return true;
    }
    return false;
}

char Bishop::getPieceType() const {
    return 'B';
}

bool Bishop::pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
    return isDiagonalClear(src, dest, GameBoard);
}