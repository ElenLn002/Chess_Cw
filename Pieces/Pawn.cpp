#include "Pawn.hpp"

Pawn::Pawn(PieceColour colour) : Piece(colour), hasMoved(false), colour(colour) {}

bool Pawn::pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
    return true;
}

bool Pawn::move(Position src, Position dest) {
    int dir = (colour == PieceColour::White) ? 1 : -1;

    if (!hasMoved && (src.row + dir == dest.row || src.row + 2 * dir == dest.row) && src.col == dest.col) {
        hasMoved = true;
        return true;
    }
    else if (hasMoved && src.col == dest.col && src.row + dir == dest.row) {
        return true;
    }
    else if (src.row + dir == dest.row && (src.col + 1 == dest.col || src.col - 1 == dest.col)) {
        return true;
    }
    return false;
}

char Pawn::getPieceType() const {
    return 'P';
}