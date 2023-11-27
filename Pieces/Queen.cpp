#include "Queen.hpp"

Queen::Queen(PieceColour colour) : Piece(colour), colour(colour) {}

bool Queen::move(Position src, Position dest) {
    if (abs(src.row - dest.row) == abs(src.col - dest.col) || src.row == dest.row || src.col == dest.col) {
        return true;
    }
    return false;
}

char Queen::getPieceType() const {
    return 'Q';
}

bool Queen::pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
    return isHorizontalClear(src, dest, GameBoard) || isVerticalClear(src, dest, GameBoard) || isDiagonalClear(src, dest, GameBoard);
}
