#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"

class Bishop : public Piece
{
public:
    Bishop(PieceColour color, const QString path) : Piece(color, path, PieceType::Bishop) {}
    ~Bishop() {}

private:
    std::unique_ptr<Piece> Clone() const override ;
    bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]);
};
#endif
