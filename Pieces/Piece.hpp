#ifndef PIECE_HPP
#define PIECE_HPP

#include "Includes.hpp"
#include "Const.hpp"

class Piece {
public:
    Piece(PieceColour colour);
    virtual bool move(Position src, Position dest) = 0;
    virtual bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) = 0;

    bool pieceValidation(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);

    ~Piece() = default;

    PieceColour getColour() const { return colour_; };
    virtual char getPieceType() const = 0;


protected: //Helpers
    bool isSpotEmpty(Position pos, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);
    bool isDiagonalClear(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);
    bool isHorizontalClear(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);
    bool isVerticalClear(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);

private:
    PieceColour colour_;
};

#endif // !PIECE_HPP
