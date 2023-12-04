#include "King.hpp"

King::King(PieceColour colour) : Piece(colour), hasMoved(false), colour(colour) {}

bool King::move(Position src, Position dest) {
    if ((abs(src.row - dest.row) <= 1) && (abs(src.col - dest.col) <= 1)) {
        hasMoved = true;
        return true;
    }
    return false;
}

char King::getPieceType() const {
    return 'K';
}