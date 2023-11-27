#ifndef BOARD_HPP
#define BOARD_HPP

#include "Includes.hpp"
#include "Const.hpp"
#include "Piece.hpp"
#include "PieceIncludes.hpp"

class Board {
public:
    Board();
    // Piece* getPieceAtPosition(Position pos) const;
    std::unique_ptr<Piece> board[BOARD_SIZE][BOARD_SIZE];

private:

    void initializePawns();
    void initializeFigures(PieceColour colour, int row);

};
#endif // !BOARD_HPP
