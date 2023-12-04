//#include <iostream>
//#include <math.h>
//#include <memory>
//#include <vector>
//#include <string>
//#include <stdexcept>
//

#include "GameController.hpp"

//const int BOARD_SIZE = 8;
//const int NUM_OF_PLAYERS = 2;
//
//enum class PieceColour { White, Black };
//enum class SpotColour { White, Black };
//
//struct Position {
//    int row; 
//    int col;
//};


//class Piece {
//public:
//    Piece(PieceColour colour);
//    virtual bool move(Position src, Position dest) = 0;
//    virtual bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) = 0;
//
//    bool pieceValidation(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);
//
//    ~Piece() = default;
//
//    PieceColour getColour() const { return colour_; };
//    virtual char getPieceType() const = 0;
//
//
//protected: //Helpers
//    bool isSpotEmpty(Position pos, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);    
//    bool isDiagonalClear(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);
//    bool isHorizontalClear(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);
//    bool isVerticalClear(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);
//
//private:
//    PieceColour colour_;
//};
//
//
//
//Piece::Piece(PieceColour colour) : colour_(colour) {}
//
////Validation
//bool Piece:: pieceValidation(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
//    Piece* destPiece = GameBoard[dest.row][dest.col].get();
//
//    // Check if destination spot is empty or has an opponent's piece
//    if (!destPiece || (GameBoard[src.row][src.col]->getColour() != destPiece->getColour())) {
//        // Check if the move is valid for the specific piece
//        return GameBoard[src.row][src.col]->move(src, dest);
//    }
//    return false;
//}
//
////Helpers
//
//bool Piece:: isSpotEmpty(Position pos, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
//    if (pos.row < 0 || pos.row >= BOARD_SIZE || pos.col < 0 || pos.col >= BOARD_SIZE) {
//        throw std::out_of_range("Position is out of bounds");
//    }
//    return !GameBoard[pos.row][pos.col];
//}
//
//bool Piece::isDiagonalClear(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
//    int rowDiff = dest.row - src.row;
//    int colDiff = dest.col - src.col;
//    if (abs(rowDiff) != abs(colDiff)) {
//        return false; // Not a diagonal move
//    }
//
//    int rowIncrement = (rowDiff > 0) ? 1 : -1;
//    int colIncrement = (colDiff > 0) ? 1 : -1;
//
//    int checkRow = src.row + rowIncrement;
//    int checkCol = src.col + colIncrement;
//
//    while (checkRow != dest.row && checkCol != dest.col) {
//        if (!isSpotEmpty({ checkRow, checkCol }, GameBoard)) {
//            return false; // Path not clear
//        }
//        checkRow += rowIncrement;
//        checkCol += colIncrement;
//    }
//    return true; // Path clear
//}
//
//bool Piece:: isHorizontalClear(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
//    if (src.row != dest.row) {
//        return false; // Not a horizontal move
//    }
//
//    int minCol = std::min(src.col, dest.col);
//    int maxCol = std::max(src.col, dest.col);
//    for (int col = minCol + 1; col < maxCol; ++col) {
//        if (!isSpotEmpty({ src.row, col }, GameBoard)) {
//            return false; // Path not clear
//        }
//    }
//    return true; // Path clear
//}
//
//bool Piece:: isVerticalClear(const Position& src, const Position& dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
//    if (src.col != dest.col) {
//        return false; // Not a vertical move
//    }
//
//    int minRow = std::min(src.row, dest.row);
//    int maxRow = std::max(src.row, dest.row);
//    for (int row = minRow + 1; row < maxRow; ++row) {
//        if (!isSpotEmpty({ row, src.col }, GameBoard)) {
//            return false; // Path not clear
//        }
//    }
//    return true; // Path clear
//}
//
//class Pawn : public Piece {
//public:
//    Pawn(PieceColour colour);
//    bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) override;
//    bool move(Position src, Position dest) override;
//    char getPieceType() const;
//
//private:
//    bool hasMoved;
//    PieceColour colour;
//
//};
//
//Pawn::Pawn(PieceColour colour) : Piece(colour), hasMoved(false), colour(colour){}
//
//bool Pawn:: pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
//    return true;
//}
//
//bool Pawn::move(Position src, Position dest) {
//    int dir = (colour == PieceColour::White) ? 1 : -1;
//
//    if (!hasMoved && (src.row + dir == dest.row || src.row + 2 * dir == dest.row) && src.col == dest.col) {
//        hasMoved = true;
//        return true;
//    }
//    else if (hasMoved && src.col == dest.col && src.row + dir == dest.row) {
//        return true;
//    }
//    else if (src.row + dir == dest.row && (src.col + 1 == dest.col || src.col - 1 == dest.col)) {
//        return true;
//    }
//    return false;
//}
//
//char Pawn::getPieceType() const {
//    return 'P';
//}
//
//class Rook : public Piece {
//private:
//    bool hasMoved;
//    PieceColour colour;
//
//public:
//    Rook(PieceColour colour);
//    bool move(Position src, Position dest) override;
//    bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) override;
//    char getPieceType() const;
//};
//
//Rook::Rook(PieceColour colour) : Piece(colour), hasMoved(false), colour(colour) {}
//
//bool Rook::move(Position src, Position dest) {
//    if (src.row == dest.row || src.col == dest.col) {
//        return true;
//    }
//    return false;
//}
//
//char Rook::getPieceType() const {
//    return 'R';
//}
//
//bool Rook::pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
//    return isHorizontalClear(src, dest, GameBoard) || isVerticalClear(src, dest, GameBoard);
//}
//
//
//class Knight : public Piece {
//private:
//    PieceColour colour;
//
//public:
//    Knight(PieceColour colour);
//    bool move(Position src, Position dest) override;
//    bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) override {
//        return true;
//    }
//    char getPieceType() const;
//};
//
//Knight::Knight(PieceColour colour) : Piece(colour), colour(colour) {}
//
//bool Knight::move(Position src, Position dest) {
//    if (src.col == dest.col + 2 || src.col == dest.col - 2) {
//        if (src.row == dest.row + 1 || src.row == dest.row - 1) {
//            return true;
//        }
//    }
//
//    if (src.col == dest.col + 1 || src.col == dest.col - 1) {
//        if (src.row == dest.row + 2 || src.row == dest.row - 2) {
//            return true;
//        }
//    }
//    return false;
//}
//
//char Knight::getPieceType() const {
//    return 'N';
//}
//
//class Bishop : public Piece {
//private:
//    PieceColour colour;
//
//public:
//    Bishop(PieceColour colour);
//    bool move(Position src, Position dest) override;
//    char getPieceType() const;
//    bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) override;
//};
//
//Bishop::Bishop(PieceColour colour) : Piece(colour), colour(colour) {}
//
//bool Bishop::move(Position src, Position dest) {
//    if (abs(src.row - dest.row) == abs(src.col - dest.col)) {
//        return true;
//    }
//    return false;
//}
//
//char Bishop::getPieceType() const {
//    return 'B';
//}
//
//bool Bishop::pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
//    return isDiagonalClear(src, dest, GameBoard);
//}
//
//class Queen : public Piece {
//private:
//    PieceColour colour;
//
//public:
//    Queen(PieceColour colour);
//    bool move(Position src, Position dest) override;
//    char getPieceType() const;
//    bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) override;
//};
//
//Queen::Queen(PieceColour colour) : Piece(colour), colour(colour) {}
//
//bool Queen::move(Position src, Position dest) {
//    if (abs(src.row - dest.row) == abs(src.col - dest.col) || src.row == dest.row || src.col == dest.col) {
//        return true;
//    }
//    return false;
//}
//
//char Queen::getPieceType() const {
//    return 'Q';
//}
//
//bool Queen::pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
//    return isHorizontalClear(src, dest, GameBoard) || isVerticalClear(src, dest, GameBoard) || isDiagonalClear(src, dest, GameBoard);
//}
//
//class King : public Piece {
//private:
//    bool hasMoved;
//    PieceColour colour;
//
//public:
//    King(PieceColour colour);
//    bool move(Position src, Position dest) override;
//    bool pathValidation(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) override {
//        return true;
//    }
//    char getPieceType() const;
//};
//
//King::King(PieceColour colour) : Piece(colour), hasMoved(false), colour(colour) {}
//
//bool King::move(Position src, Position dest) {
//    if ((abs(src.row - dest.row) <= 1) && (abs(src.col - dest.col) <= 1)) {
//        hasMoved = true;
//        return true;
//    }
//    return false;
//}
//
//char King::getPieceType() const {
//    return 'K';
//}


//class Board {
//public:
//    Board();
//   // Piece* getPieceAtPosition(Position pos) const;
//    std::unique_ptr<Piece> board[BOARD_SIZE][BOARD_SIZE];
//
//private:
//    
//    void initializePawns();
//    void initializeFigures(PieceColour colour, int row);
//
//};
//
//void Board::initializePawns() {
//    for (int i = 0; i < BOARD_SIZE; ++i) {
//        board[1][i] = std::make_unique<Pawn>(PieceColour::White);
//        board[6][i] = std::make_unique<Pawn>(PieceColour::Black);
//    }
//}
//
//void Board::initializeFigures(PieceColour colour, int row) {
//    board[row][0] = std::make_unique<Rook>(colour);
//    board[row][1] = std::make_unique<Knight>(colour);
//    board[row][2] = std::make_unique<Bishop>(colour);
//    board[row][3] = std::make_unique<King>(colour);
//    board[row][4] = std::make_unique<Queen>(colour);
//    board[row][5] = std::make_unique<Bishop>(colour);
//    board[row][6] = std::make_unique<Knight>(colour);
//    board[row][7] = std::make_unique<Rook>(colour);
//}
//
//Board::Board() {
//    for (int i = 0; i < BOARD_SIZE; ++i) {
//        for (int j = 0; j < BOARD_SIZE; ++j) {
//            SpotColour colour = ((i + j) % 2 == 0) ? SpotColour::White : SpotColour::Black;
//            Position pos = { i, j };
//            board[i][j] = nullptr; // Initialize all board positions to nullptr
//        }
//    }
//
//    // Set up Pawns
//    for (int i = 0; i < BOARD_SIZE; ++i) {
//        board[1][i] = std::make_unique<Pawn>(PieceColour::White);
//        board[6][i] = std::make_unique<Pawn>(PieceColour::Black);
//    }
//
//    // Set up other pieces
//    initializeFigures(PieceColour::White, 0);
//    initializeFigures(PieceColour::Black, 7);
//
//    std::cout << "Board ctor\n";
//}

//class GameLogic {
//public:
//    GameLogic();
//    void switchTurn();
//    bool isInCheck(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour);
//    bool validateMove(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);
//    bool isCheckmate(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour);
//    bool isStalemate(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour);
//    //bool isDraw(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour);
//    bool makeMove(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]);
//    PieceColour currentPlayer;
//};

//GameLogic::GameLogic() : currentPlayer(PieceColour::White) {}
//
//void GameLogic::switchTurn() {
//    currentPlayer = (currentPlayer == PieceColour::White) ? PieceColour::Black : PieceColour::White;
//}
//
//
//bool GameLogic::isInCheck(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour) {
//    Position kingPos = { -1, -1 }; // Initialize to an invalid position
//
//    // Find the position of the king of the specified color on the board
//    for (int i = 0; i < BOARD_SIZE; ++i) {
//        for (int j = 0; j < BOARD_SIZE; ++j) {
//            if (GameBoard[i][j] && GameBoard[i][j]->getColour() == colour &&
//                GameBoard[i][j]->getPieceType() == 'K') {
//                kingPos = { i, j };
//                break;
//            }
//        }
//        if (kingPos.row != -1) {
//            break;
//        }
//    }
//
//    if (kingPos.row == -1) {
//        // King not found; handle this scenario
//        return false;
//    }
//
//    // Iterate through the entire board to look for opponent's pieces
//    for (int i = 0; i < BOARD_SIZE; ++i) {
//        for (int j = 0; j < BOARD_SIZE; ++j) {
//            if (GameBoard[i][j] && GameBoard[i][j]->getColour() != colour) {
//                // Check if the opponent's piece can attack the king
//                if (GameBoard[i][j]->move({ i, j }, kingPos)) {
//                    // There is a piece that can attack the king
//                    return true;
//                }
//            }
//        }
//    }
//
//    return false;
//}
//
//bool GameLogic::isCheckmate(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour) {
//    // Check if the current player's king is in check
//    if (!isInCheck(GameBoard, colour)) {
//        return false; // King is not in check, hence not checkmate
//    }
//
//    // Iterate through the current player's pieces to check if any move can escape the check
//    for (int i = 0; i < BOARD_SIZE; ++i) {
//        for (int j = 0; j < BOARD_SIZE; ++j) {
//            if (GameBoard[i][j] && GameBoard[i][j]->getColour() == colour) {
//                for (int k = 0; k < BOARD_SIZE; ++k) {
//                    for (int l = 0; l < BOARD_SIZE; ++l) {
//                        if (GameBoard[i][j]->move({ i, j }, { k, l })) {
//                            std::unique_ptr<Piece> tempPiece = std::move(GameBoard[k][l]);
//                            std::swap(GameBoard[i][j], GameBoard[k][l]);
//
//                            bool isSafeMove = !isInCheck(GameBoard, colour);
//
//                            // Undo the move
//                            std::swap(GameBoard[i][j], GameBoard[k][l]);
//                            GameBoard[k][l] = std::move(tempPiece);
//
//                            if (isSafeMove) {
//                                return false; // A legal move found, not checkmate
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return true; // No legal moves found, checkmate
//}
//
//bool GameLogic::isStalemate(std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE], PieceColour colour) {
//    // Check if the current player's king is in check
//    if (isInCheck(GameBoard, colour)) {
//        return false; // If the king is in check, it's not a stalemate
//    }
//
//    // Iterate through the current player's pieces to check if any move can be made
//    for (int i = 0; i < BOARD_SIZE; ++i) {
//        for (int j = 0; j < BOARD_SIZE; ++j) {
//            if (GameBoard[i][j] && GameBoard[i][j]->getColour() == colour) {
//                for (int k = 0; k < BOARD_SIZE; ++k) {
//                    for (int l = 0; l < BOARD_SIZE; ++l) {
//                        if (GameBoard[i][j]->move({ i, j }, { k, l })) {
//                            std::unique_ptr<Piece> tempPiece = std::move(GameBoard[k][l]);
//                            std::swap(GameBoard[i][j], GameBoard[k][l]);
//
//                            bool isSafeMove = !isInCheck(GameBoard, colour);
//
//                            // Undo the move
//                            std::swap(GameBoard[i][j], GameBoard[k][l]);
//                            GameBoard[k][l] = std::move(tempPiece);
//
//                            if (isSafeMove) {
//                                return false; // A legal move found, not a stalemate
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return true; // No legal moves found, stalemate
//}
//
//bool GameLogic::validateMove(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
//    if (src.row < 0 || src.row >= BOARD_SIZE || src.col < 0 || src.col >= BOARD_SIZE ||
//        dest.row < 0 || dest.row >= BOARD_SIZE || dest.col < 0 || dest.col >= BOARD_SIZE) {
//        return false; // Invalid positions
//    }
//    if (!GameBoard[src.row][src.col]) {
//        return false; // No piece at source
//    }
//    Piece* pieceAtSrc = GameBoard[src.row][src.col].get();
//
//    if (!pieceAtSrc->move(src, dest)) {
//        return false; // Invalid move for the piece
//    }
//    if (!GameBoard[dest.row][dest.col] || pieceAtSrc->getColour() != GameBoard[dest.row][dest.col]->getColour()) {
//        std::unique_ptr<Piece> tempDestPiece = std::move(GameBoard[dest.row][dest.col]);
//
//        GameBoard[dest.row][dest.col] = std::move(GameBoard[src.row][src.col]);
//        GameBoard[src.row][src.col] = nullptr;
//
//        PieceColour currentColour = pieceAtSrc->getColour();
//        Position kingPos;
//        bool moveOpensCheck = isInCheck(GameBoard, currentColour);
//
//        // Undo the simulated move
//        GameBoard[src.row][src.col] = std::move(GameBoard[dest.row][dest.col]);
//        GameBoard[dest.row][dest.col] = std::move(tempDestPiece);
//
//        if (moveOpensCheck) {
//            return false; // Move opens a path to the current player's king
//        }
//
//        if (pieceAtSrc->pathValidation(src, dest, GameBoard)) {
//            return true; // Valid move
//        }
//    }
//
//    return false;
//}
//
//bool GameLogic::makeMove(Position src, Position dest, std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE]) {
//    Piece* pieceToMove = GameBoard[src.row][src.col].get();
//
//    if (!pieceToMove || pieceToMove->getColour() != currentPlayer || !validateMove(src, dest, GameBoard)) {
//        return false; // Invalid move
//    }
//
//    std::unique_ptr<Piece> tempDestPiece = std::move(GameBoard[dest.row][dest.col]);
//    std::swap(GameBoard[src.row][src.col], GameBoard[dest.row][dest.col]);
//
//    if (isInCheck(GameBoard, currentPlayer)) {
//        std::swap(GameBoard[src.row][src.col], GameBoard[dest.row][dest.col]);
//        GameBoard[dest.row][dest.col] = std::move(tempDestPiece);
//        return false; // Move leaves own king in check
//    }
//
//    switchTurn();
//    return true; // Move executed successfully
//}

//class GameController {
//public:
//    static GameController& getInstance() {
//         static GameController instance; // Singleton instance
//            return instance;
//    }
//
//    GameController(const GameController&) = delete; // Delete copy constructor
//    GameController& operator=(const GameController&) = delete;
//
//    void startGame();
//    void printBoard();
//    void getUserInput(Position& src, Position& dest);
//    void playGame();
//
//private:
//    GameController();
//    Board gameBoard;
//    GameLogic gameLogic;
//    bool isGameOver;
//};
//
//GameController::GameController() : isGameOver(false) {}
//
//void GameController::printBoard() {
//    std::cout << "  a b c d e f g h\n";
//    for (int i = 0; i < BOARD_SIZE; ++i) {
//        std::cout << BOARD_SIZE - i << " ";
//        for (int j = 0; j < BOARD_SIZE; ++j) {
//            if (gameBoard.board[i][j]) {
//                std::cout << gameBoard.board[i][j]->getPieceType() << " ";
//            }
//            else {
//                std::cout << ". ";
//            }
//        }
//        std::cout << BOARD_SIZE - i << "\n";
//    }
//    std::cout << "  a b c d e f g h\n";
//}
//
//void GameController::getUserInput(Position& src, Position& dest) {
//    std::string input;
//
//    std::cout << "Enter source position (e.g., 'a2'): ";
//    std::cin >> input;
//
//    if (input.size() != 2 || !isalpha(input[0]) || !isdigit(input[1])) {
//        std::cout << "Invalid input format. Please enter a valid position." << std::endl;
//        getUserInput(src, dest);
//        return;
//    }
//
//    char srcCol = input[0];
//    int srcRow = input[1] - '0'; // Convert char to int
//
//    // Convert column character to index
//    src.col = srcCol - 'a';
//    src.row = BOARD_SIZE - srcRow; // Adjust row to match the board index, subtract 1 from BOARD_SIZE
//
//    std::cout << "Source position: " << srcCol << srcRow << " -> Position: " << src.row << ", " << src.col << std::endl;
//
//    std::cout << "Enter destination position (e.g., 'b4'): ";
//    std::cin >> input;
//
//    if (input.size() != 2 || !isalpha(input[0]) || !isdigit(input[1])) {
//        std::cout << "Invalid input format. Please enter a valid position." << std::endl;
//        getUserInput(src, dest);
//        return;
//    }
//
//    char destCol = input[0];
//    int destRow = input[1] - '0'; // Convert char to int
//
//    // Convert column character to index
//    dest.col = destCol - 'a';
//    dest.row = BOARD_SIZE - destRow; // Adjust row to match the board index, subtract 1 from BOARD_SIZE
//
//    std::cout << "Destination position: " << destCol << destRow << " -> Position: " << dest.row << ", " << dest.col << std::endl;
//}
//
//
//
//
//
//void GameController::playGame() {
//    while (!isGameOver) {
//        printBoard();
//
//        Position src, dest;
//        getUserInput(src, dest);
//
//        bool moveSuccess = gameLogic.makeMove(src, dest, gameBoard.board);
//
//        if (!moveSuccess) {
//            std::cout << "Invalid move. Please try again." << std::endl;
//            continue;
//        }
//
//        isGameOver = gameLogic.isCheckmate(gameBoard.board, gameLogic.currentPlayer);
//
//        if (isGameOver) {
//            std::cout << "Checkmate! Game over." << std::endl;
//            break;
//        }
//
//        if (gameLogic.isStalemate(gameBoard.board, gameLogic.currentPlayer)) {
//            std::cout << "Stalemate! Game over." << std::endl;
//            break;
//        }
//
//        gameLogic.switchTurn();
//    }
//
//    // Print the final board state
//    printBoard();
//}
//
//
//void GameController::startGame() {
//    isGameOver = false;
//    while (!isGameOver) {
//        printBoard();
//        Position src, dest;
//        getUserInput(src, dest);
//
//        bool moveSuccess = gameLogic.makeMove(src, dest, gameBoard.board);
//
//        if (!moveSuccess) {
//            std::cout << "Invalid move. Please try again." << std::endl;
//            continue;
//        }
//
//        isGameOver = gameLogic.isCheckmate(gameBoard.board, gameLogic.currentPlayer);
//
//        if (isGameOver) {
//            std::cout << "Checkmate! Game over." << std::endl;
//            break;
//        }
//
//        if (gameLogic.isStalemate(gameBoard.board, gameLogic.currentPlayer)) {
//            std::cout << "Stalemate! Game over." << std::endl;
//            break;
//        }
//
//        gameLogic.switchTurn();
//    }
//
//    // Print the final board state
//    printBoard();
//}
//
int main() {
    GameController& gameController = GameController::getInstance();
    gameController.startGame();

    return 0;
}


