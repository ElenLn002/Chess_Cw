#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"

class Rook : public Piece {
private:
    bool hasMoved;
    PieceColour colour;

public:
    Rook(PieceColour colour);
    bool move(Position src, Position dest) override;
    bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) override;
    char getPieceType() const;
};

#endif 
