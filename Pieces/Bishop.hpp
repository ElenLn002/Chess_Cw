#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"

class Bishop : public Piece {
private:
    PieceColour colour;

public:
    Bishop(PieceColour colour);
    bool move(Position src, Position dest) override;
    char getPieceType() const;
    bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) override;
};


#endif 
