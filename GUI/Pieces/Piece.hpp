#ifndef PIECE_HPP
#define PIECE_HPP

#include "Includes.hpp"
#include "QtIncludes.hpp"
#include "Definitions.hpp"

class Piece {
protected:
    PieceType type_;

public:
    Piece(PieceColour color, QString path, PieceType type) : color_(color), path_(path), type_(type) {}
    ~Piece() {}
    QString GetPieceImagePath() const;
    virtual std::unique_ptr<Piece> Clone() const = 0;
    PieceColour getColor() const;
    PieceType getPieceType() const; 
    bool isLegalMove(Position src, Position dest, const std::unique_ptr<Piece>(&GameBoard)[BOARD_SIZE][BOARD_SIZE]);

private:
    virtual bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) = 0;
    PieceColour color_;
    QString path_;

};

#endif 