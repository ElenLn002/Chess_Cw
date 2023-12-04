#include "GameLogic.hpp"

GameLogic::GameLogic() : currentPlayer(PieceColour::White) {}

void GameLogic::switchTurn() {
    currentPlayer = (currentPlayer == PieceColour::White) ? PieceColour::Black : PieceColour::White;
}


bool GameLogic::isInCheck(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour) {
    Position kingPos = { -1, -1 }; 

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (GameBoard[i][j] && GameBoard[i][j]->getColour() == colour &&
                GameBoard[i][j]->getPieceType() == 'K') {
                kingPos = { i, j };
                break;
            }
        }
        if (kingPos.row != -1) {
            break;
        }
    }

    if (kingPos.row == -1) {
        return false;
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (GameBoard[i][j] && GameBoard[i][j]->getColour() != colour) {
                if (GameBoard[i][j]->move({ i, j }, kingPos)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool GameLogic::isCheckmate(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour) {
    if (!isInCheck(GameBoard, colour)) {
        return false; // King is not in check, hence not checkmate
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (GameBoard[i][j] && GameBoard[i][j]->getColour() == colour) {
                for (int k = 0; k < BOARD_SIZE; ++k) {
                    for (int l = 0; l < BOARD_SIZE; ++l) {
                        if (GameBoard[i][j]->move({ i, j }, { k, l })) {
                            std::unique_ptr<Piece> tempPiece = std::move(GameBoard[k][l]);
                            std::swap(GameBoard[i][j], GameBoard[k][l]);

                            bool isSafeMove = !isInCheck(GameBoard, colour);

                            // Undo the move
                            std::swap(GameBoard[i][j], GameBoard[k][l]);
                            GameBoard[k][l] = std::move(tempPiece);

                            if (isSafeMove) {
                                return false; // A legal move found, not checkmate
                            }
                        }
                    }
                }
            }
        }
    }

    return true; // No legal moves found, checkmate
}

bool GameLogic::isStalemate(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour) {
    if (isInCheck(GameBoard, colour)) {
        return false; 
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (GameBoard[i][j] && GameBoard[i][j]->getColour() == colour) {
                for (int k = 0; k < BOARD_SIZE; ++k) {
                    for (int l = 0; l < BOARD_SIZE; ++l) {
                        if (GameBoard[i][j]->move({ i, j }, { k, l })) {
                            std::unique_ptr<Piece> tempPiece = std::move(GameBoard[k][l]);
                            std::swap(GameBoard[i][j], GameBoard[k][l]);
                            bool isSafeMove = !isInCheck(GameBoard, colour);

                            // Undo the move
                            std::swap(GameBoard[i][j], GameBoard[k][l]);
                            GameBoard[k][l] = std::move(tempPiece);

                            if (isSafeMove) {
                                return false; // A legal move found, not a stalemate
                            }
                        }
                    }
                }
            }
        }
    }

    return true; // No legal moves found, stalemate
}

bool GameLogic::validateMove(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
    if (src.row < 0 || src.row >= BOARD_SIZE || src.col < 0 || src.col >= BOARD_SIZE ||
        dest.row < 0 || dest.row >= BOARD_SIZE || dest.col < 0 || dest.col >= BOARD_SIZE) {
        return false; // Invalid positions
    }
    if (!GameBoard[src.row][src.col]) {
        return false; // No piece at source
    }
    Piece* pieceAtSrc = GameBoard[src.row][src.col].get();

    if (!pieceAtSrc->move(src, dest)) {
        return false; // Invalid move for the piece
    }
    if (!GameBoard[dest.row][dest.col] || pieceAtSrc->getColour() != GameBoard[dest.row][dest.col]->getColour()) {
        std::unique_ptr<Piece> tempDestPiece = std::move(GameBoard[dest.row][dest.col]);

        GameBoard[dest.row][dest.col] = std::move(GameBoard[src.row][src.col]);
        GameBoard[src.row][src.col] = nullptr;

        PieceColour currentColour = pieceAtSrc->getColour();
        Position kingPos;
        bool moveOpensCheck = isInCheck(GameBoard, currentColour);

        // Undo the simulated move
        GameBoard[src.row][src.col] = std::move(GameBoard[dest.row][dest.col]);
        GameBoard[dest.row][dest.col] = std::move(tempDestPiece);

        if (moveOpensCheck) {
            return false; // Move opens a path to the current player's king
        }

        if (pieceAtSrc->pathValidation(src, dest, GameBoard)) {
            return true; // Valid move
        }
    }

    return false;
}

bool GameLogic::makeMove(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
    Piece* pieceToMove = GameBoard[src.row][src.col].get();

    if (!pieceToMove || pieceToMove->getColour() != currentPlayer || !validateMove(src, dest, GameBoard)) {
        return false; // Invalid move
    }

    std::unique_ptr<Piece> tempDestPiece = std::move(GameBoard[dest.row][dest.col]);
    std::swap(GameBoard[src.row][src.col], GameBoard[dest.row][dest.col]);

    if (isInCheck(GameBoard, currentPlayer)) {
        std::swap(GameBoard[src.row][src.col], GameBoard[dest.row][dest.col]);
        GameBoard[dest.row][dest.col] = std::move(tempDestPiece);
        return false; // Move leaves own king in check
    }

    switchTurn();
    return true; // Move executed successfully
}
