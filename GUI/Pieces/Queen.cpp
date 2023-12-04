#include "Queen.hpp"

    std::unique_ptr<Piece> Queen:: Clone() const override {
        return std::make_unique<Queen>(*this);
    }

    bool Queen:: moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) {
        if (src.row == dest.row) {
            int iColOffset = (dest.col - src.col > 0) ? 1 : -1;
            for (int iCheckCol = src.col + iColOffset; iCheckCol != dest.col; iCheckCol = iCheckCol + iColOffset) {
                if (GameBoard[src.row][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if (dest.col == src.col) {
            int iRowOffset = (dest.row - src.row > 0) ? 1 : -1;
            for (int iCheckRow = src.row + iRowOffset; iCheckRow != dest.row; iCheckRow = iCheckRow + iRowOffset) {
                if (GameBoard[iCheckRow][src.col] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if ((dest.col - src.col == dest.row - src.row) || (dest.col - src.col == src.row - dest.row)) {
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
