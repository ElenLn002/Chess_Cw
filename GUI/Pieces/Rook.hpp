#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"

class Rook : public Piece
{
public:
    Rook(PieceColour color, const QString path) : Piece(color, path, PieceType::Rook) {}
    ~Rook() {}

private:
    std::unique_ptr<Piece> Clone() const override;
    bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]);
#endif
