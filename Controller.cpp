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


void Controller::Menu() {
    std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
    std::cout << "\t\t\t\t\t\t_______________________________________________" << std::endl;
    std::cout << "\t\t\t\t\t\t|                                             |" << std::endl;
    std::cout << "\t\t\t\t\t\t| Hello this is Chess platform designed by Ln |" << std::endl;
    std::cout << "\t\t\t\t\t\t|                                             |" << std::endl;
    std::cout << "\t\t\t\t\t\t|              Start (S)                      |" << std::endl;
    std::cout << "\t\t\t\t\t\t|              Options (O)                    |" << std::endl;
    std::cout << "\t\t\t\t\t\t|              Moves (M)                      |" << std::endl;
    std::cout << "\t\t\t\t\t\t|              Records (R)                    |" << std::endl;
    std::cout << "\t\t\t\t\t\t|              Quit (Q)                       |" << std::endl;
    std::cout << "\t\t\t\t\t\t|                                             |" << std::endl;
    std::cout << "\t\t\t\t\t\t| In any time to stop the game type Z0        |" << std::endl;
    std::cout << "\t\t\t\t\t\t|      instead of field coordinates           |" << std::endl;
    std::cout << "\t\t\t\t\t\t|                                             |" << std::endl;
    std::cout << "\t\t\t\t\t\t          Your Choice: ";
    std::cin >> choice;

    switch (choice) {
    case 83: // ascii S
        //Start();
        break;
    case 79: // ascii O
        system("clear");
        std::cout << " WP = White pawn &  BP = Black pawn" << std::endl;
        std::cout << " WN = White Knight & BN = Black Knight" << std::endl;
        std::cout << " WB = White Bishop & BB = Black Bishop" << std::endl;
        std::cout << " WR = White Rook & BR = Black Rook" << std::endl;
        std::cout << " WQ = White Queen & BQ = Black Queen" << std::endl;
        std::cout << " WK = White King & BK =Black King" << std::endl << std::endl;
        std::cout << " To move a piece, write current field coordinates (letter than number) press 'Enter' and write target field coordinates"<<std::endl;
        std::cout << "    Press 'B' for back to Menu   " << std::endl << std::endl;
        std::cout << "    For back : ";// << std::endl;
        std::cin >> choice;
        if (choice == 66) { // ascii B
            system("clear");
            Menu();
        }
    case 81: //Q
        exit(EXIT_FAILURE);
    case 77: //M
        system("clear");
        std::cout << "Pawn - except for its first move, the pawn moves one square forward." << std::endl << std::endl;
        std::cout << "Rook - the rook moves in a straight line forward or sideways across unoccupied squares." << std::endl << std::endl;
        std::cout << "Knight - the knight, is the only piece that can jump over another piece." << std::endl << std::endl;
        std::cout << "Bishop - the bishop moves on a diagonal and is restricted to the color of its starting square. " << std::endl << std::endl;
        std::cout << "Queen - the queen can move across any number of unoccupied squares in any direction." << std::endl << std::endl;
        std::cout << "King - like the queen, the king can move in any direction but only one square." << std::endl << std::endl << std::endl;
        std::cout << "    Press 'B' for back to Menu   " << std::endl << std::endl;
        std::cout << "    For back : ";// << std::endl;
        std::cin >> choice;
        if (choice == 66) {
            system("clear");
            Menu();
        }
    case 82:
    system ("clear");
    std::cout<<"\tHere you can find top 10 rated chessplayers of the world"<<std::endl<<std::endl;
    std::cout<<"\t1. Magnus Carlsen       (NOR)  2859"<<std::endl;
    std::cout<<"\t2. Ding Liren           (CHN)  2811"<<std::endl;
    std::cout<<"\t3. Ian Nepomniachtchi   (RUS)  2793"<<std::endl;
    std::cout<<"\t4. Alireza Firouzja     (FRA)  2785"<<std::endl;
    std::cout<<"\t5. Hikaru Nakamura      (USA)  2768"<<std::endl;
    std::cout<<"\t6. Fabiano Caruana      (USA)  2766"<<std::endl;
    std::cout<<"\t7. Anish Giri           (NED)  2764"<<std::endl;
    std::cout<<"\t8. Wesley So            (USA)  2760"<<std::endl;
    std::cout<<"\t9. Viswanathan Anand    (IND)  2754"<<std::endl;
    std::cout<<"\t10.Sergey Karjakin      (RUS)  2747"<<std::endl<<std::endl;
    std::cout<<"Press 'B' for back to Menu "<<std::endl<<std::endl; 
    std::cout << "    For back : ";// << std::endl;
        std::cin >> choice;
        if (choice == 66) {
            system("clear");
            Menu();
        }





    }

}
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

