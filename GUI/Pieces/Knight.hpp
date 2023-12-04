#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"

class Knight : public Piece
{
public:
    Knight(PieceColour color, const QString path) : Piece(color, path, PieceType::Knight) {}
    ~Knight() {}

private:
    std::unique_ptr<Piece> Clone() const override;
    bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]);

#endif
