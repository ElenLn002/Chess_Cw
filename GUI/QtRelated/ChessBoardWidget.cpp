#include "ChessBoardWidget.hpp"

void ChessBoardWidget:: paintEvent(QPaintEvent* event) override {
    Q_UNUSED(event);
    QPainter painter(this);
    BoardDrawer::drawChessboard(painter); // Draw the chessboard
    BoardDrawer::drawPieces(painter, boardManager_); // Draw the pieces
    if (selectedPiece_) {
        BoardDrawer::highlightSquare(painter, selectedPiecePosition_); // Highlight the selected square
    }
}

void ChessBoardWidget:: mousePressEvent(QMouseEvent* event) override
{
    Position clickedSquare = calculateSquareIndex(event->pos());
    Piece* clickedPiece = boardManager_.getPieceAt(clickedSquare);

    if (clickedPiece && clickedPiece->GetColor() == boardManager_.currentPlayer_)
    {
        selectedPiece_ = clickedPiece;
        selectedPiecePosition_ = clickedSquare;
        update(); // Trigger a repaint to show selection
    }

    QWidget::mousePressEvent(event);

}

void ChessBoardWidget:: mouseReleaseEvent(QMouseEvent* event) override
{
    Position destinationSquare = calculateSquareIndex(event->pos());

    if (selectedPiece_) {
        // Attempt to move the selected piece
        if (boardManager_.movePiece(selectedPiecePosition_, destinationSquare))
        {
            boardManager_.currentPlayer_ = (boardManager_.currentPlayer_ == PieceColour::White) ? PieceColour::Black : PieceColour::White;
            selectedPiece_ = nullptr; // Deselect after successful move
            update(); // Trigger a repaint after the move
        }
    }
}

 Position ChessBoardWidget:: calculateSquareIndex(const QPoint& position) {
     int col = position.x() / SQUARE_SIZE;
     int row = position.y() / SQUARE_SIZE;

     if (col >= 0 && col < BOARD_SIZE && row >= 0 && row < BOARD_SIZE) {
         return Position{ row, col };
     }

     return Position{ -1, -1 };
 }
