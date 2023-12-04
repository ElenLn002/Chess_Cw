#include "Piece.hpp"

Piece::Piece(PieceColour colour) : colour_(colour) {}

//Validation
bool Piece::pieceValidation(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
    Piece* destPiece = GameBoard[dest.row][dest.col].get();

    // Check if destination spot is empty or has an opponent's piece
    if (!destPiece || (GameBoard[src.row][src.col]->getColour() != destPiece->getColour())) {
        // Check if the move is valid for the specific piece
        return GameBoard[src.row][src.col]->move(src, dest);
    }
    return false;
}

//Helpers

bool Piece::isSpotEmpty(Position pos, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
    if (pos.row < 0 || pos.row >= BOARD_SIZE || pos.col < 0 || pos.col >= BOARD_SIZE) {
        throw std::out_of_range("Position is out of bounds");
    }
    return !GameBoard[pos.row][pos.col];
}

bool Piece::isDiagonalClear(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
    int rowDiff = dest.row - src.row;
    int colDiff = dest.col - src.col;
    if (abs(rowDiff) != abs(colDiff)) {
        return false; // Not a diagonal move
    }

    int rowIncrement = (rowDiff > 0) ? 1 : -1;
    int colIncrement = (colDiff > 0) ? 1 : -1;

    int checkRow = src.row + rowIncrement;
    int checkCol = src.col + colIncrement;

    while (checkRow != dest.row && checkCol != dest.col) {
        if (!isSpotEmpty({ checkRow, checkCol }, GameBoard)) {
            return false; // Path not clear
        }
        checkRow += rowIncrement;
        checkCol += colIncrement;
    }
    return true; // Path clear
}

bool Piece::isHorizontalClear(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
    if (src.row != dest.row) {
        return false; // Not a horizontal move
    }

    int minCol = std::min(src.col, dest.col);
    int maxCol = std::max(src.col, dest.col);
    for (int col = minCol + 1; col < maxCol; ++col) {
        if (!isSpotEmpty({ src.row, col }, GameBoard)) {
            return false; // Path not clear
        }
    }
    return true; // Path clear
}

bool Piece::isVerticalClear(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
    if (src.col != dest.col) {
        return false; // Not a vertical move
    }

    int minRow = std::min(src.row, dest.row);
    int maxRow = std::max(src.row, dest.row);
    for (int row = minRow + 1; row < maxRow; ++row) {
        if (!isSpotEmpty({ row, src.col }, GameBoard)) {
            return false; // Path not clear
        }
    }
    return true; // Path clear
}