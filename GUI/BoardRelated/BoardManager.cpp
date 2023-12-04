#include "BoardManager.hpp"

BoardManager:: BoardManager(const BoardManager& other) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (other.GameBoard[i][j]) {
               GameBoard[i][j] = other.GameBoard[i][j]->Clone();
            }
            else {
                GameBoard[i][j] = nullptr;
            }
        }
    }
}

void BoardManager:: InitBoard() {
    // Place white pieces
    for (int i = 0; i < BOARD_SIZE; ++i) {
        GameBoard[6][i] = std::make_unique<Pawn>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wP.png");
        GameBoard[1][i] = std::make_unique<Pawn>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bP.png");

    }
    GameBoard[0][0] = std::make_unique<Rook>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bR.png");
    GameBoard[0][1] = std::make_unique<Knight>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bN.png");
    GameBoard[0][2] = std::make_unique<Bishop>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bB.png");
    GameBoard[0][3] = std::make_unique<Queen>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bQ.png");
    GameBoard[0][4] = std::make_unique<King>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bK.png");
    GameBoard[0][5] = std::make_unique<Bishop>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bB.png");
    GameBoard[0][6] = std::make_unique<Knight>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bN.png");
    GameBoard[0][7] = std::make_unique<Rook>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bR.png");

    GameBoard[7][0] = std::make_unique<Rook>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wR.png");
    GameBoard[7][1] = std::make_unique<Knight>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wN.png");
    GameBoard[7][2] = std::make_unique<Bishop>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wB.png");
    GameBoard[7][3] = std::make_unique<Queen>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wQ.png");
    GameBoard[7][4] = std::make_unique<King>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wK.png");
    GameBoard[7][5] = std::make_unique<Bishop>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wB.png");
    GameBoard[7][6] = std::make_unique<Knight>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wN.png");
    GameBoard[7][7] = std::make_unique<Rook>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wR.png");

    // Initialize other squares as nullptr
    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            GameBoard[i][j] = nullptr;
        }
    }
}

Piece* BoardManager:: getPieceAt(Position position) const {
    return GameBoard[position.row][position.col].get();
}


bool BoardManager:: validateMove(Position src, Position dest) const {
    Piece* srcPiece = getPieceAt(src);
    if (srcPiece == nullptr) {
        return false;
    }
    if (dest.row < 0 || dest.row >= BOARD_SIZE || dest.col < 0 || dest.col >= BOARD_SIZE) {
        return false;
    }
    Piece* destPiece = getPieceAt(dest);
    if (destPiece != nullptr && srcPiece->GetColor() == destPiece->GetColor()) {
        return false;
    }

    return srcPiece->IsLegalMove(src, dest, GameBoard);
}

bool BoardManager:: movePiece(Position src, Position dest) {
    Piece* pieceAtSrc = getPieceAt(src);
    if (!validateMove(src, dest)) {
        return false; // Move is not valid
    }

    GameBoard[dest.row][dest.col] = std::move(GameBoard[src.row][src.col]);
    GameBoard[src.row][src.col] = nullptr;

    return true; // Successful move
}
