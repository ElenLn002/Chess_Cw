#include "Knight.hpp"

Knight::Knight(PieceColour colour) : Piece(colour), colour(colour) {}

bool Knight::move(Position src, Position dest) {
    if (src.col == dest.col + 2 || src.col == dest.col - 2) {
        if (src.row == dest.row + 1 || src.row == dest.row - 1) {
            return true;
        }
    }

    if (src.col == dest.col + 1 || src.col == dest.col - 1) {
        if (src.row == dest.row + 2 || src.row == dest.row - 2) {
            return true;
        }
    }
    return false;
}

char Knight::getPieceType() const {
    return 'N';
}
