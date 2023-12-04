#include "BoardDrawer.hpp"

static void BoardDrawer:: drawChessboard(QPainter& painter) {
    // Define the frame width and color
    QColor frameColor(72, 60, 50); // Dark brown color

    // Draw the frame
    painter.fillRect(0, 0, SQUARE_SIZE * BOARD_SIZE + 2 * FRAME_SIZE, FRAME_SIZE, frameColor); // Top frame
    painter.fillRect(0, 0, FRAME_SIZE, SQUARE_SIZE * BOARD_SIZE + 2 * FRAME_SIZE, frameColor); // Left frame
    painter.fillRect(0, SQUARE_SIZE * BOARD_SIZE + FRAME_SIZE, SQUARE_SIZE * BOARD_SIZE + 2 * FRAME_SIZE, FRAME_SIZE, frameColor); // Bottom frame
    painter.fillRect(SQUARE_SIZE * BOARD_SIZE + FRAME_SIZE, 0, FRAME_SIZE, SQUARE_SIZE * BOARD_SIZE + 2 * FRAME_SIZE, frameColor); // Right frame

    // Adjust the starting point of the chessboard squares
    int offset = FRAME_SIZE;

    // Create and display the chessboard grid using alternating colors
    QColor lightColor(217, 195, 161); // Light square color
    QColor darkColor(150, 120, 89);   // Dark square color

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            QColor squareColor = ((i + j) % 2 == 0) ? lightColor : darkColor;
            painter.fillRect(offset + SQUARE_SIZE * j, offset + SQUARE_SIZE * i, SQUARE_SIZE, SQUARE_SIZE, squareColor);
        }
    }
}


static void BoardDrawer:: drawPieces(QPainter& painter, BoardManager& boardManager) {
    // Iterate through the board and draw the pieces on the squares
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            Piece* piece = boardManager.getPieceAt(Position{ i, j });
            if (piece) {
                QString pieceImagePath = piece->GetPieceImagePath();
                QPixmap pieceImage(pieceImagePath);
                // Define the offset to center the pieces on the squares
                const int pieceOffset = (SQUARE_SIZE - pieceImage.width()) / 2;
                // Adjust the position to center the piece on the square
                int x = SQUARE_SIZE * j + pieceOffset + FRAME_SIZE; // Added FRAME_SIZE to the x coordinate
                int y = SQUARE_SIZE * i + pieceOffset + FRAME_SIZE; // Added FRAME_SIZE to the y coordinate
                painter.drawPixmap(x, y, pieceImage);
            }
        }
    }
}

static void BoardDrawer:: highlightSquare(QPainter& painter, const Position& squarePosition) {
    // Define the frame width if not already defined
    const int FRAME_SIZE = 10; // Adjust the width as needed

    painter.setPen(QPen(Qt::red ,4));
    painter.setBrush(Qt::transparent);
    // Add FRAME_SIZE to the x and y coordinates to account for the frame
    painter.drawRect(FRAME_SIZE + SQUARE_SIZE * squarePosition.col, FRAME_SIZE + SQUARE_SIZE * squarePosition.row, SQUARE_SIZE, SQUARE_SIZE);
}
