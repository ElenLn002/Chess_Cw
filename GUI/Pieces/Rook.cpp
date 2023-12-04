#include "Rook.hpp"

std::unique_ptr<Piece> Rook:: Clone() const override {
    return std::make_unique<Rook>(*this);
}

bool Rook:: moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) {
    if (src.row == dest.row) {
        int iColOffset = (dest.col - src.col > 0) ? 1 : -1;
        for (int iCheckCol = src.col + iColOffset; iCheckCol != dest.col; iCheckCol = iCheckCol + iColOffset) {
            if (GameBoard[src.row][src.col] != 0) {
                return false;
            }
        }
        return true;
    }
    else if (dest.col == src.col) {
        int iRowOffset = (dest.row - src.row > 0) ? 1 : -1;
        for (int iCheckRow = src.row + iRowOffset; iCheckRow != dest.row; iCheckRow = iCheckRow + iRowOffset) {
            if (GameBoard[src.row][src.col] != 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}
