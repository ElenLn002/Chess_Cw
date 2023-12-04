#include " Pawn.hpp"

bool Pawn:: isTwoStepsForward(Position src, Position dest, PieceColour color) const {
    return (color == PieceColour::White && dest.row == src.row - 2) ||
        (color == PieceColour::Black && dest.row == src.row + 2);
}

std::unique_ptr<Piece> Pawn:: Clone() const override {
    return std::make_unique<Pawn>(*this);
}


bool Pawn:: moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) override {
    // Check if the destination is out of bounds
    if (dest.row < 0 || dest.row >= BOARD_SIZE || dest.col < 0 || dest.col >= BOARD_SIZE) {
        return false;
    }

    const std::unique_ptr<Piece>& destSpot = GameBoard[dest.row][dest.col];
    int direction = (GetColor() == PieceColour::White) ? -1 : 1;
    int startRow = (GetColor() == PieceColour::White) ? 6 : 1;

    // Move one square forward
    if (!destSpot && src.col == dest.col && dest.row == src.row + direction) {
        return true;
    }

    // Move two squares forward from the starting position
    if (!destSpot && src.col == dest.col && src.row == startRow &&
        dest.row == src.row + 2 * direction && !GameBoard[src.row + direction][src.col]) {
        return true;
    }

    // Capture diagonally
    if (destSpot && std::abs(dest.col - src.col) == 1 && dest.row == src.row + direction) {
        return true;
    }

    return false;
}
