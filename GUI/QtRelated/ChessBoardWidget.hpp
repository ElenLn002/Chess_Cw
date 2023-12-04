#ifndef CHESSBOARDWIDGET_HPP
#define CHESSBOARDWIDGET_HPP

#include "Includes.hpp"
#include "QtIncludes.hpp"
#include "Definitions.hpp"

class ChessBoardWidget : public QWidget {
    Q_OBJECT

public:
    explicit ChessBoardWidget(QWidget* parent = nullptr)
        : QWidget(parent), selectedPiece_(nullptr), selectedPiecePosition_{ -1, -1 } {}


protected:

    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Position calculateSquareIndex(const QPoint& position);
    Piece* selectedPiece_;
    Position selectedPiecePosition_;
    BoardManager boardManager_;
};
#endif 