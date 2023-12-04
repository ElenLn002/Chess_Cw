#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"

class Queen : public Piece
{
public:
    Queen(PieceColour color, const QString path) : Piece(color, path, PieceType::Queen) {}
    ~Queen() {}

private:
    std::unique_ptr<Piece> Clone() const override;
    bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]);
};

#endif
