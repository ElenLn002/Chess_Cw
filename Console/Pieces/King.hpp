#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece{
private:
    bool hasMoved;
    PieceColour colour;

public:
    King(PieceColour colour);
    bool move(Position src, Position dest) override;
    bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) override {
        return true;
    }
    char getPieceType() const;
};


#endif 
