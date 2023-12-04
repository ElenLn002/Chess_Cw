#include "Knight.hpp"

std::unique_ptr<Piece> Knight:: Clone() const override {
    return std::make_unique<Knight>(*this);
}

bool Knight:: moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) {
    if ((src.col == dest.col + 1) || (src.col == dest.col - 1)) {
        if ((src.row == dest.row + 2) || (src.row == dest.row - 2)) {
            return true;
        }
    }
    if ((src.col == dest.col + 2) || (src.col == dest.col - 2)) {
        if ((src.row == dest.row + 1) || (src.row == dest.row - 1)) {
            return true;
        }
    }
    return false;
}
