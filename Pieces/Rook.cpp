#include "Rook.hpp"

Rook::Rook(PieceColour colour) : Piece(colour), hasMoved(false), colour(colour) {}

bool Rook::move(Position src, Position dest) {
    if (src.row == dest.row || src.col == dest.col) {
        return true;
    }
    return false;
}

char Rook::getPieceType() const {
    return 'R';
}

bool Rook::pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
    return isHorizontalClear(src, dest, GameBoard) || isVerticalClear(src, dest, GameBoard);
}