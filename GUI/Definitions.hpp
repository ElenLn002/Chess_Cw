#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP


const int BOARD_SIZE = 8;
const int SQUARE_SIZE = 50;
const int FRAME_SIZE = 10;

enum class PieceColour { White, Black };
enum class PieceType { Pawn, Rook, Knight, Bishop, Queen, King };

struct Position {
    int row;
    int col;
};

#endif // !DEFINITIONS_HPP
