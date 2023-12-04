#include "Bishop.hpp"

std::unique_ptr<Piece> Bishop:: Clone() const override {
    return std::make_unique<Bishop>(*this);
}

bool Bishop: moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) {
    if ((dest.col - src.col == dest.row - src.row) || (dest.col - src.col == src.row - dest.row)) {
        // Make sure that all invervening squares are empty
        int iRowOffset = (dest.row - src.row > 0) ? 1 : -1;
        int iColOffset = (dest.col - src.col > 0) ? 1 : -1;
        int iCheckRow;
        int iCheckCol;
        for (iCheckRow = src.row + iRowOffset, iCheckCol = src.col + iColOffset;
            iCheckRow != dest.row;
            iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
        {
            if (GameBoard[iCheckRow][iCheckCol] != 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}
