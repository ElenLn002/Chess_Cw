#include "BoardChecks.hpp"

BoardChecks::BoardChecks() {
    for (int Row = 0; Row < 8; ++Row) {
        for (int Col = 0; Col < 8; ++Col) {
            GameBoard[Row][Col] = 0;
        }
    }
    // Allocate and place white pieces
    for (int Col = 0; Col < 8; ++Col) {
        GameBoard[1][Col] = new Pawn('W');
    }
    GameBoard[0][0] = new Rook('W');
    GameBoard[0][1] = new Knight('W');
    GameBoard[0][2] = new Bishop('W');
    GameBoard[0][3] = new Queen('W');
    GameBoard[0][4] = new King('W');
    GameBoard[0][5] = new Bishop('W');
    GameBoard[0][6] = new Knight('W');
    GameBoard[0][7] = new Rook('W');

    // Allocate and place black pieces
    for (int Col = 0; Col < 8; ++Col) {
        GameBoard[6][Col] = new Pawn('B');
    }
    GameBoard[7][0] = new Rook('B');
    GameBoard[7][1] = new Knight('B');
    GameBoard[7][2] = new Bishop('B');
    GameBoard[7][3] = new Queen('B');
    GameBoard[7][4] = new King('B');
    GameBoard[7][5] = new Bishop('B');
    GameBoard[7][6] = new Knight('B');
    GameBoard[7][7] = new Rook('B');

}
BoardChecks::~BoardChecks() {
    for (int Row = 0; Row < 8; ++Row) {
        for (int Col = 0; Col < 8; ++Col) {
            delete GameBoard[Row][Col];
        }
    }
}

void BoardChecks::PrintBoard() {
    std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
    const int SquareWidth = 4;
    const int SquareHeight = 3;
    for (int Row = 0; Row < 8 * SquareHeight; ++Row) {
        int SquareRow = Row / SquareHeight;
        // Print side border with numbering
        if (Row % 3 == 1) {
            std::cout << "\t\t\t-" << (8 - SquareRow);
        }
        else {
            
            std::cout << "\t\t\t__";
        }
        // Print the chess board
        for (int Col = 0; Col < 8 * SquareWidth; ++Col) {
            int SquareCol = Col / SquareWidth;
            if (((Row % 3) == 1) && ((Col % 4) == 1 || (Col % 4) == 2) && GameBoard[7 - SquareRow][SquareCol] != 0) {
                if ((Col % 4) == 1) {
                    std::cout << GameBoard[7 - SquareRow][SquareCol]->GetColor();
                }
                else {
                    std::cout << GameBoard[7 - SquareRow][SquareCol]->GetPiece();
                }
            }
            else {
                if ((SquareRow + SquareCol) % 2 == 1) {
                    std::cout << ' ';
                }
                else {
                    std::cout << '*';
                }
            }
        }
        std::cout << std::endl;
    }
    // Print the bottom border with numbers

    char UpperCaseLetter = 65;
    for (int Row = 0; Row < SquareHeight; ++Row) {
        if (Row % 3 == 1) {
            std::cout << "\t\t\t__";
            for (int Col = 0; Col < 8 * SquareWidth; ++Col) {
                int SquareCol = Col / SquareWidth;
                if ((Col % 4) == 1) {
                    std::cout << (char)(UpperCaseLetter);
                    UpperCaseLetter++;
                }
                else {
                    std::cout << "-";
                }
            }
            std::cout << std::endl;
        }
        else {
            std::cout<<"\t\t\t";
            for (int Col = 1; Col < 9 * SquareWidth; ++Col) {
                std::cout << "_";
            }
            std::cout << std::endl;
        }
    }
}


bool BoardChecks::IsInCheck(char PieceColor) {
    // Find the king
    int KingRow;
    int KingCol;
    for (int Row = 0; Row < 8; ++Row) {
        for (int Col = 0; Col < 8; ++Col) {
            if (GameBoard[Row][Col] != 0) {
                if (GameBoard[Row][Col]->GetColor() == PieceColor) {
                    if (GameBoard[Row][Col]->GetPiece() == 'K') {
                        KingRow = Row;
                        KingCol = Col;
                    }
                }
            }
        }
    }
    // Run through the opponent's pieces and see if any can take the king
    for (int Row = 0; Row < 8; ++Row) {
        for (int Col = 0; Col < 8; ++Col) {
            if (GameBoard[Row][Col] != 0) {
                if (GameBoard[Row][Col]->GetColor() != PieceColor) {
                    if (GameBoard[Row][Col]->isMoveValid(Row, Col, KingRow, KingCol, GameBoard)) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool BoardChecks::CanMove(char PieceColor) {
    // Run through all pieces
    for (int Row = 0; Row < 8; ++Row) {
        for (int Col = 0; Col < 8; ++Col) {
            if (GameBoard[Row][Col] != 0) {
                // If it is a piece of the current player, see if it has a legal move
                if (GameBoard[Row][Col]->GetColor() == PieceColor) {
                    for (int MoveRow = 0; MoveRow < 8; ++MoveRow) {
                        for (int MoveCol = 0; MoveCol < 8; ++MoveCol) {
                            if (GameBoard[Row][Col]->isMoveValid(Row, Col, MoveRow, MoveCol, GameBoard)) {
                                // Make move and check whether king is in check
                                Piece* temp = GameBoard[MoveRow][MoveCol];
                                GameBoard[MoveRow][MoveCol] = GameBoard[Row][Col];
                                GameBoard[Row][Col] = 0;
                                bool canMove = !IsInCheck(PieceColor);
                                // Undo the move
                                GameBoard[Row][Col] = GameBoard[MoveRow][MoveCol];
                                GameBoard[MoveRow][MoveCol] = temp;
                                if (canMove) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

