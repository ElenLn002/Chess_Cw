#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"

class Knight : public Piece {
private:
    PieceColour colour;

public:
    Knight(PieceColour colour);
    bool move(Position src, Position dest) override;
    bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) override {
        return true;
    }
    char getPieceType() const;
};


#endif 
