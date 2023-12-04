#include "King.hpp"

std::unique_ptr<Piece> King:: Clone() const override {
    return std::make_unique<King>(*this);
}

bool King:: moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) {
    int iRowDelta = dest.row - src.row;
    int iColDelta = dest.col - src.col;
    if (((iRowDelta >= -1) && (iRowDelta <= 1)) &&
        ((iColDelta >= -1) && (iColDelta <= 1)))
    {
        return true;
    }
    return false;
}
