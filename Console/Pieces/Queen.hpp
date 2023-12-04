#ifndef QUEEN_HPP   
#define QUEEN_HPP

#include "Piece.hpp"

class Queen : public Piece {
private:
    PieceColour colour;

public:
    Queen(PieceColour colour);
    bool move(Position src, Position dest) override;
    char getPieceType() const;
    bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) override;
};


#endif 
