#ifndef BOARDDRAWER_HPP
#define BOARDDRAWER_HPP

#include "Includes.hpp"
#include "QtIncludes.hpp"
#include "Definitions.hpp"

class BoardDrawer {
public:
    static void drawChessboard(QPainter& painter); 
    static void drawPieces(QPainter& painter, BoardManager& boardManager);
    static void highlightSquare(QPainter& painter, const Position& squarePosition);

private:
    static constexpr int FRAME_THICKNESS = 5;
};

#endif
