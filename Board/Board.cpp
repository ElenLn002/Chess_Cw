#include "Board.hpp"

void Board::initializePawns() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[1][i] = std::make_unique<Pawn>(PieceColour::White);
        board[6][i] = std::make_unique<Pawn>(PieceColour::Black);
    }
}

void Board::initializeFigures(PieceColour colour, int row) {
    board[row][0] = std::make_unique<Rook>(colour);
    board[row][1] = std::make_unique<Knight>(colour);
    board[row][2] = std::make_unique<Bishop>(colour);
    board[row][3] = std::make_unique<King>(colour);
    board[row][4] = std::make_unique<Queen>(colour);
    board[row][5] = std::make_unique<Bishop>(colour);
    board[row][6] = std::make_unique<Knight>(colour);
    board[row][7] = std::make_unique<Rook>(colour);
}

Board::Board() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            SpotColour colour = ((i + j) % 2 == 0) ? SpotColour::White : SpotColour::Black;
            Position pos = { i, j };
            board[i][j] = nullptr; // Initialize all board positions to nullptr
        }
    }

    // Set up Pawns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[1][i] = std::make_unique<Pawn>(PieceColour::White);
        board[6][i] = std::make_unique<Pawn>(PieceColour::Black);
    }

    // Set up other pieces
    initializeFigures(PieceColour::White, 0);
    initializeFigures(PieceColour::Black, 7);

    std::cout << "Board ctor\n";
}
