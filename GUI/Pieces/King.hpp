#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece
{
public:
    King(PieceColour color,const QString path) : Piece(color, path, PieceType::King) {}
    ~King() {}

private:

    std::unique_ptr<Piece> Clone() const override;
    bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]);
};

#endif
