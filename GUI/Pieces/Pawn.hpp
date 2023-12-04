#ifndef PAWN_HPP
#define PAWN_HPP
#include "Piece.hpp"

class Pawn : public Piece
{
public:
    Pawn(PieceColour color, const QString path) : Piece(color, path, PieceType::Pawn) {}
    ~Pawn() {}

   
private: //Helpers
    bool isTwoStepsForward(Position src, Position dest, PieceColour color) const;
    std::unique_ptr<Piece> Clone() const override;
    bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) override;

};

#endif
