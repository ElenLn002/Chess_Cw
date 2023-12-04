#include "Piece.hpp"

QString Piece:: GetPieceImagePath() const {
    return path_;
}

PieceColour Piece:: getColor() const {
    return color_;
}

PieceType Piece::getPieceType() const {
    return type_;
}
bool Piece:: isLegalMove(Position src, Position dest, const std::unique_ptr<Piece>(&GameBoard)[BOARD_SIZE][BOARD_SIZE]) {
    if (dest.row < 0 || dest.row >= BOARD_SIZE || dest.col < 0 || dest.col >= BOARD_SIZE) {
        return false;
    }

    Piece* destSpot = GameBoard[dest.row][dest.col].get();
    if (!destSpot || color_ != destSpot->getColor()) {
        return moveValidation(src, dest, GameBoard);
    }
    return false;
}