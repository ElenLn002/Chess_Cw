#ifndef CONST_HPP
#define CONST_HPP

const int BOARD_SIZE = 8;
const int NUM_OF_PLAYERS = 2;

enum class PieceColour { White, Black };
enum class SpotColour { White, Black };

struct Position {
    int row;
    int col;
};

#endif // !CONST_HPP
