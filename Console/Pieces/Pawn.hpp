#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(PieceColour colour);
    bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) override;
    bool move(Position src, Position dest) override;
    char getPieceType() const;

private:
    bool hasMoved;
    PieceColour colour;

};
#endif 
