#include "Controller.hpp"

Controller::Controller() {
    PlayerTurn = 'W';
    choice = 0;
    for (int Row = 0; Row < 8; ++Row) {
        for (int Col = 0; Col < 8; ++Col) {
            chessPiece[Row][Col] = 0;
        }
    }
   
}
Controller::~Controller() {}

void Controller::Start() {
	system ("clear");
    Menu();
    do {
        GetNextMove(chessGameBoard.GameBoard);
        MoveTurn();
    } while (!IsGameOver());
    chessGameBoard.PrintBoard();

}

void Controller::GetNextMove(Piece* GameBoard[8][8]) {
    bool ValidMove = false;
    do {
        system("clear");

        //std::cout << "Rule for move is :" << std::endl;
        //std::cout << "Move by selecting row & column to another valid location using row & column" << std::endl << std::endl << std::endl;
        chessGameBoard.PrintBoard();

        // Get input and convert to coordinates
        std::cout <<std::endl<<"\t\t\t"<< PlayerTurn << "\'s Move: ";
        char StartMoveCol;
        int StartMoveRow;
        std::cin >> StartMoveCol >> StartMoveRow;
        if (StartMoveCol == 98 && StartMoveRow == 0) {
            exit(EXIT_FAILURE);
        }
       
        int StartRow = StartMoveRow - 1;
        int StartCol = (int)StartMoveCol - 65;

        std::cout << "\t\t\tTo: ";
        char EndMoveCol;
        int EndMoveRow;
        std::cin >> EndMoveCol >> EndMoveRow;
        if (EndMoveCol == 98 && EndMoveRow == 0) {
            exit(EXIT_FAILURE);
        }
       /* if (EndMoveCol == 80 && EndMoveRow == 0) {
            chessPiece[StartMoveRow][StartMoveCol]->PrintPossibleMoves(StartMoveRow, StartMoveCol, EndMoveRow, EndMoveCol, GameBoard);
            break;
        }*/
        int EndRow = EndMoveRow - 1;
        int EndCol = (int)EndMoveCol - 65;

        // Check that the indices are in range
        // and that the source and destination are different
        if ((StartRow >= 0 && StartRow <= 7) &&
            (StartCol >= 0 && StartCol <= 7) &&
            (EndRow >= 0 && EndRow <= 7) &&
            (EndCol >= 0 && EndCol <= 7)) {
            // Additional checks in here
            Piece* CurrPiece = GameBoard[StartRow][StartCol];
            // Check that the piece is the correct color
            if ((CurrPiece != 0) && (CurrPiece->GetColor() == PlayerTurn)) {
                // Check that the destination is a valid destination
                if (CurrPiece->isMoveValid(StartRow, StartCol, EndRow, EndCol, GameBoard)) {
                    // Make the move
                    Piece* Temp = GameBoard[EndRow][EndCol];
                    GameBoard[EndRow][EndCol] = GameBoard[StartRow][StartCol];
                    GameBoard[StartRow][StartCol] = 0;
                    //Make sure that the current player is not in check
                    if (!chessGameBoard.IsInCheck(PlayerTurn)) {
                        delete Temp;
                        ValidMove = true;
                    }
                    //else { // Undo the last move
                    //    if (StartCol == 85 && StartRow == 0) {
                    //        GameBoard[StartRow][StartCol] = GameBoard[EndRow][EndCol];
                    //        GameBoard[EndRow][EndCol] = Temp;
                    //    }
                    //    
                    //}
                }
            }
        }
       
    } while (!ValidMove);
}

void Controller::MoveTurn() {
    PlayerTurn = (PlayerTurn == 'W') ? 'B' : 'W';
}

bool Controller::IsGameOver() {
    bool CanMove(false);
    CanMove = chessGameBoard.CanMove(PlayerTurn);
    if (!CanMove) {
        if (chessGameBoard.IsInCheck(PlayerTurn)) {
            MoveTurn();
            std::cout << "Checkmate, " << PlayerTurn << " Wins!" << std::endl;
        }
        else {
            std::cout << "Stalemate!" << std::endl;
        }
    }
    return !CanMove;
}

