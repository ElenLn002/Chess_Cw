#include <QApplication>
#include <QWidget>
#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QColor>
#include <QVBoxLayout>
#include <QPalette>
#include <QPaintEvent>
#include <QMainWindow>

#include <iostream>
#include <math.h>
#include <memory>
#include <vector>
#include <string>
#include <vector>
#include <stdexcept>

const int BOARD_SIZE = 8;
const int SQUARE_SIZE = 50;
const int FRAME_SIZE = 10;

enum class PieceColour { White, Black };
enum class PieceType { Pawn, Rook, Knight, Bishop, Queen, King };

struct Position {
    int row;
    int col;
};

class Piece {
protected:
    PieceType type_;

public:
    Piece(PieceColour color, QString path, PieceType type) : color_(color), path_(path), type_(type)  {}
    ~Piece() {}
    QString GetPieceImagePath() const {
        return path_;
    }

    virtual std::unique_ptr<Piece> Clone() const = 0;
    PieceColour GetColor() const {
        return color_;
    }

    PieceType getPieceType() const {
        return type_;
    }
    bool IsLegalMove(Position src, Position dest, const std::unique_ptr<Piece>(&GameBoard)[BOARD_SIZE][BOARD_SIZE]) {
        if (dest.row < 0 || dest.row >= BOARD_SIZE || dest.col < 0 || dest.col >= BOARD_SIZE) {
            return false;
        }

        Piece* destSpot = GameBoard[dest.row][dest.col].get();
        if (!destSpot || color_ != destSpot->GetColor()) {
            return moveValidation(src, dest, GameBoard);
        }
        return false;
    }

private:
    virtual bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) = 0;
    PieceColour color_;
    QString path_;

protected:
    
};

class Pawn : public Piece
{
public:
    Pawn(PieceColour color, const QString path) : Piece(color, path, PieceType::Pawn) {}
    ~Pawn() {}

   
private: //Helpers
    bool isTwoStepsForward(Position src, Position dest, PieceColour color) const {
        return (color == PieceColour::White && dest.row == src.row - 2) ||
            (color == PieceColour::Black && dest.row == src.row + 2);
    }

    std::unique_ptr<Piece> Clone() const override {
        return std::make_unique<Pawn>(*this);
    }


    bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) override {
        // Check if the destination is out of bounds
        if (dest.row < 0 || dest.row >= BOARD_SIZE || dest.col < 0 || dest.col >= BOARD_SIZE) {
            return false;
        }

        const std::unique_ptr<Piece>& destSpot = GameBoard[dest.row][dest.col];
        int direction = (GetColor() == PieceColour::White) ? -1 : 1;
        int startRow = (GetColor() == PieceColour::White) ? 6 : 1;

        // Move one square forward
        if (!destSpot && src.col == dest.col && dest.row == src.row + direction) {
            return true;
        }

        // Move two squares forward from the starting position
        if (!destSpot && src.col == dest.col && src.row == startRow &&
            dest.row == src.row + 2 * direction && !GameBoard[src.row + direction][src.col]) {
            return true;
        }

        // Capture diagonally
        if (destSpot && std::abs(dest.col - src.col) == 1 && dest.row == src.row + direction) {
            return true;
        }

        return false;
    }

};

class Knight : public Piece
{
public:
    Knight(PieceColour color, const QString path) : Piece(color, path, PieceType::Knight) {}
    ~Knight() {}

    
private:
    std::unique_ptr<Piece> Clone() const override {
        return std::make_unique<Knight>(*this);
    }

    bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) {
        if ((src.col == dest.col + 1) || (src.col == dest.col - 1)) {
            if ((src.row == dest.row + 2) || (src.row == dest.row - 2)) {
                return true;
            }
        }
        if ((src.col == dest.col + 2) || (src.col == dest.col - 2)) {
            if ((src.row == dest.row + 1) || (src.row == dest.row - 1)) {
                return true;
            }
        }
        return false;
    }
};

class Bishop : public Piece
{
public:
    Bishop(PieceColour color, const QString path) : Piece(color, path, PieceType::Bishop) {}
    ~Bishop() {}

private:


    std::unique_ptr<Piece> Clone() const override {
        return std::make_unique<Bishop>(*this);
    }

    bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) {
        if ((dest.col - src.col == dest.row - src.row) || (dest.col - src.col == src.row - dest.row)) {
            // Make sure that all invervening squares are empty
            int iRowOffset = (dest.row - src.row > 0) ? 1 : -1;
            int iColOffset = (dest.col - src.col > 0) ? 1 : -1;
            int iCheckRow;
            int iCheckCol;
            for (iCheckRow = src.row + iRowOffset, iCheckCol = src.col + iColOffset;
                iCheckRow != dest.row;
                iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
            {
                if (GameBoard[iCheckRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Rook : public Piece
{
public:
    Rook(PieceColour color, const QString path) : Piece(color, path, PieceType::Rook) {}
    ~Rook() {}

private:
        std::unique_ptr<Piece> Clone() const override {
        return std::make_unique<Rook>(*this);
    }

    bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) {
        if (src.row == dest.row) {
            int iColOffset = (dest.col - src.col > 0) ? 1 : -1;
            for (int iCheckCol = src.col + iColOffset; iCheckCol != dest.col; iCheckCol = iCheckCol + iColOffset) {
                if (GameBoard[src.row][src.col] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if (dest.col == src.col) {
            int iRowOffset = (dest.row - src.row > 0) ? 1 : -1;
            for (int iCheckRow = src.row + iRowOffset; iCheckRow != dest.row; iCheckRow = iCheckRow + iRowOffset) {
                if (GameBoard[src.row][src.col] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Queen : public Piece
{
public:
    Queen(PieceColour color, const QString path) : Piece(color, path, PieceType::Queen) {}
    ~Queen() {}

    
private:
    std::unique_ptr<Piece> Clone() const override {
        return std::make_unique<Queen>(*this);
    }

    bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) {
        if (src.row == dest.row) {
            int iColOffset = (dest.col - src.col > 0) ? 1 : -1;
            for (int iCheckCol = src.col + iColOffset; iCheckCol != dest.col; iCheckCol = iCheckCol + iColOffset) {
                if (GameBoard[src.row][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if (dest.col == src.col) {
            int iRowOffset = (dest.row - src.row > 0) ? 1 : -1;
            for (int iCheckRow = src.row + iRowOffset; iCheckRow != dest.row; iCheckRow = iCheckRow + iRowOffset) {
                if (GameBoard[iCheckRow][src.col] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if ((dest.col - src.col == dest.row - src.row) || (dest.col - src.col == src.row - dest.row)) {
            int iRowOffset = (dest.row - src.row > 0) ? 1 : -1;
            int iColOffset = (dest.col - src.col > 0) ? 1 : -1;
            int iCheckRow;
            int iCheckCol;
            for (iCheckRow = src.row + iRowOffset, iCheckCol = src.col + iColOffset;
                iCheckRow != dest.row;
                iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
            {
                if (GameBoard[iCheckRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class King : public Piece
{
public:
    King(PieceColour color,const QString path) : Piece(color, path, PieceType::King) {}
    ~King() {}

private:

    std::unique_ptr<Piece> Clone() const override {
        return std::make_unique<King>(*this);
    }


    bool moveValidation(Position src, Position dest, const std::unique_ptr<Piece>(*GameBoard)[BOARD_SIZE]) {
        int iRowDelta = dest.row - src.row;
        int iColDelta = dest.col - src.col;
        if (((iRowDelta >= -1) && (iRowDelta <= 1)) &&
            ((iColDelta >= -1) && (iColDelta <= 1)))
        {
            return true;
        }
        return false;
    }
};

class BoardManager {
public:
    std::unique_ptr<Piece> GameBoard[BOARD_SIZE][BOARD_SIZE];
    PieceColour currentPlayer_;

public:
    BoardManager() : currentPlayer_(PieceColour::White) {}
    // Initialize the board with pieces at their starting positions

    BoardManager(const BoardManager& other) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (other.GameBoard[i][j]) {
                   GameBoard[i][j] = other.GameBoard[i][j]->Clone();
                }
                else {
                    GameBoard[i][j] = nullptr;
                }
            }
        }
    }
    void InitBoard() {
        // Place white pieces
        for (int i = 0; i < BOARD_SIZE; ++i) {
            GameBoard[6][i] = std::make_unique<Pawn>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wP.png");
            GameBoard[1][i] = std::make_unique<Pawn>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bP.png");

        }
        GameBoard[0][0] = std::make_unique<Rook>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bR.png");
        GameBoard[0][1] = std::make_unique<Knight>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bN.png");
        GameBoard[0][2] = std::make_unique<Bishop>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bB.png");
        GameBoard[0][3] = std::make_unique<Queen>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bQ.png");
        GameBoard[0][4] = std::make_unique<King>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bK.png");
        GameBoard[0][5] = std::make_unique<Bishop>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bB.png");
        GameBoard[0][6] = std::make_unique<Knight>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bN.png");
        GameBoard[0][7] = std::make_unique<Rook>(PieceColour::Black, "C:/Users/user/Desktop/Pieces/bR.png");

        GameBoard[7][0] = std::make_unique<Rook>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wR.png");
        GameBoard[7][1] = std::make_unique<Knight>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wN.png");
        GameBoard[7][2] = std::make_unique<Bishop>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wB.png");
        GameBoard[7][3] = std::make_unique<Queen>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wQ.png");
        GameBoard[7][4] = std::make_unique<King>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wK.png");
        GameBoard[7][5] = std::make_unique<Bishop>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wB.png");
        GameBoard[7][6] = std::make_unique<Knight>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wN.png");
        GameBoard[7][7] = std::make_unique<Rook>(PieceColour::White, "C:/Users/user/Desktop/Pieces/wR.png");

        // Initialize other squares as nullptr
        for (int i = 2; i < 6; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                GameBoard[i][j] = nullptr;
            }
        }
    }

    Piece* getPieceAt(Position position) const {
        return GameBoard[position.row][position.col].get();
    }


    bool validateMove(Position src, Position dest) const {
        Piece* srcPiece = getPieceAt(src);
        if (srcPiece == nullptr) {
            return false;
        }
        if (dest.row < 0 || dest.row >= BOARD_SIZE || dest.col < 0 || dest.col >= BOARD_SIZE) {
            return false;
        }
        Piece* destPiece = getPieceAt(dest);
        if (destPiece != nullptr && srcPiece->GetColor() == destPiece->GetColor()) {
            return false;
        }

        return srcPiece->IsLegalMove(src, dest, GameBoard);
    }

    bool movePiece(Position src, Position dest) {
        Piece* pieceAtSrc = getPieceAt(src);
        if (!validateMove(src, dest)) {
            return false; // Move is not valid
        }

        GameBoard[dest.row][dest.col] = std::move(GameBoard[src.row][src.col]);
        GameBoard[src.row][src.col] = nullptr;

        return true; // Successful move
    }
};


class BoardDrawer {
public:
    static void drawChessboard(QPainter& painter) {
        // Define the frame width and color
        QColor frameColor(72, 60, 50); // Dark brown color

        // Draw the frame
        painter.fillRect(0, 0, SQUARE_SIZE * BOARD_SIZE + 2 * FRAME_SIZE, FRAME_SIZE, frameColor); // Top frame
        painter.fillRect(0, 0, FRAME_SIZE, SQUARE_SIZE * BOARD_SIZE + 2 * FRAME_SIZE, frameColor); // Left frame
        painter.fillRect(0, SQUARE_SIZE * BOARD_SIZE + FRAME_SIZE, SQUARE_SIZE * BOARD_SIZE + 2 * FRAME_SIZE, FRAME_SIZE, frameColor); // Bottom frame
        painter.fillRect(SQUARE_SIZE * BOARD_SIZE + FRAME_SIZE, 0, FRAME_SIZE, SQUARE_SIZE * BOARD_SIZE + 2 * FRAME_SIZE, frameColor); // Right frame

        // Adjust the starting point of the chessboard squares
        int offset = FRAME_SIZE;

        // Create and display the chessboard grid using alternating colors
        QColor lightColor(217, 195, 161); // Light square color
        QColor darkColor(150, 120, 89);   // Dark square color

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                QColor squareColor = ((i + j) % 2 == 0) ? lightColor : darkColor;
                painter.fillRect(offset + SQUARE_SIZE * j, offset + SQUARE_SIZE * i, SQUARE_SIZE, SQUARE_SIZE, squareColor);
            }
        }
    }


    static void drawPieces(QPainter& painter, BoardManager& boardManager) {
        // Iterate through the board and draw the pieces on the squares
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                Piece* piece = boardManager.getPieceAt(Position{ i, j });
                if (piece) {
                    QString pieceImagePath = piece->GetPieceImagePath();
                    QPixmap pieceImage(pieceImagePath);
                    // Define the offset to center the pieces on the squares
                    const int pieceOffset = (SQUARE_SIZE - pieceImage.width()) / 2;
                    // Adjust the position to center the piece on the square
                    int x = SQUARE_SIZE * j + pieceOffset + FRAME_SIZE; // Added FRAME_SIZE to the x coordinate
                    int y = SQUARE_SIZE * i + pieceOffset + FRAME_SIZE; // Added FRAME_SIZE to the y coordinate
                    painter.drawPixmap(x, y, pieceImage);
                }
            }
        }
    }



    static void highlightSquare(QPainter& painter, const Position& squarePosition) {
        // Define the frame width if not already defined
        const int FRAME_SIZE = 10; // Adjust the width as needed

        painter.setPen(QPen(Qt::red ,4));
        painter.setBrush(Qt::transparent);
        // Add FRAME_SIZE to the x and y coordinates to account for the frame
        painter.drawRect(FRAME_SIZE + SQUARE_SIZE * squarePosition.col, FRAME_SIZE + SQUARE_SIZE * squarePosition.row, SQUARE_SIZE, SQUARE_SIZE);
    }



private:
    static constexpr int FRAME_THICKNESS = 5;
};


class ChessBoardWidget : public QWidget {
    Q_OBJECT

public:
    explicit ChessBoardWidget(QWidget* parent = nullptr)
        : QWidget(parent), selectedPiece_(nullptr), selectedPiecePosition_{ -1, -1 } {}


protected:

    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        BoardDrawer::drawChessboard(painter); // Draw the chessboard
        BoardDrawer::drawPieces(painter, boardManager_); // Draw the pieces
        if (selectedPiece_) {
            BoardDrawer::highlightSquare(painter, selectedPiecePosition_); // Highlight the selected square
        }
    }

    void mousePressEvent(QMouseEvent* event) override
    {
        Position clickedSquare = calculateSquareIndex(event->pos());
        Piece* clickedPiece = boardManager_.getPieceAt(clickedSquare);

        if (clickedPiece && clickedPiece->GetColor() == boardManager_.currentPlayer_)
        {
            selectedPiece_ = clickedPiece;
            selectedPiecePosition_ = clickedSquare;
            update(); // Trigger a repaint to show selection
        }

        QWidget::mousePressEvent(event);

    }

    void mouseReleaseEvent(QMouseEvent* event) override
    {
        Position destinationSquare = calculateSquareIndex(event->pos());

        if (selectedPiece_) {
            // Attempt to move the selected piece
            if (boardManager_.movePiece(selectedPiecePosition_, destinationSquare))
            {
                boardManager_.currentPlayer_ = (boardManager_.currentPlayer_ == PieceColour::White) ? PieceColour::Black : PieceColour::White;
                selectedPiece_ = nullptr; // Deselect after successful move
                update(); // Trigger a repaint after the move
            }
        }
    }

private:
    Position calculateSquareIndex(const QPoint& position) {
        int col = position.x() / SQUARE_SIZE;
        int row = position.y() / SQUARE_SIZE;

        if (col >= 0 && col < BOARD_SIZE && row >= 0 && row < BOARD_SIZE) {
            return Position{ row, col };
        }

        return Position{ -1, -1 };
    }
public:
    Piece* selectedPiece_;
    Position selectedPiecePosition_;
    BoardManager boardManager_;
};


class GameLogic {
public:
    bool isInCheck(PieceColour playerTurn, const BoardManager& boardManager) {
        PieceColour color = (playerTurn == PieceColour::White) ? PieceColour::White : PieceColour::Black;
        // Find the king of the specified color
        Position kingPos = findKingPosition(color, boardManager);

        return isUnderAttack(kingPos, getOpponentColor(playerTurn), boardManager);
    }

    bool canMove(PieceColour PieceColor, const BoardManager& boardManager) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                Piece* piece = boardManager.getPieceAt({ i, j });
                if (piece != nullptr && piece->GetColor() == getPieceColor(PieceColor)) {
                    // Check if the piece can make a valid move
                    for (int x = 0; x < BOARD_SIZE; ++x) {
                        for (int y = 0; y < BOARD_SIZE; ++y) {
                            if (boardManager.validateMove({ i, j }, { x, y })) {
                                // Simulate the move and check if the king is in check
                                BoardManager tempBoard = boardManager;
                                tempBoard.movePiece({ i, j }, { x, y });
                                if (!isInCheck(PieceColor, tempBoard)) {
                                    return true; // Player can make a valid move
                                }
                            }
                        }
                    }
                }
            }
        }
        return false; // No valid moves for the player
    }

private:
    Position findKingPosition(PieceColour PieceColor, const BoardManager& boardManager) {
        // Helper method to find the king's position
        Position defaultPos = { -1, -1 };
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                Piece* piece = boardManager.getPieceAt({ i, j });
                if (piece != nullptr && piece->getPieceType() == PieceType::King &&
                    piece->GetColor() == getPieceColor(PieceColor)) {
                    return { i, j }; // King's position found
                }
            }
        }
        return defaultPos;
    }

    bool isUnderAttack(const Position& kingPos, PieceColour OpponentColor, const BoardManager& boardManager) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                Piece* piece = boardManager.getPieceAt({ i, j });
                if (piece != nullptr && piece->GetColor() == getPieceColor(OpponentColor)) {
                    if (boardManager.validateMove({ i, j }, kingPos)) {
                        return true; // King is under attack
                    }
                }
            }
        }
        return false;
    }

    PieceColour getOpponentColor(PieceColour PieceColor) {
        return (PieceColor == PieceColour::White) ? PieceColour::Black : PieceColour::White;
    }

    PieceColour getPieceColor(PieceColour PieceColor) {
        return (PieceColor == PieceColour::White) ? PieceColour::White : PieceColour::Black;
    }
};

class StartGameWindow : public QWidget {
    Q_OBJECT

public:
    StartGameWindow(QWidget* parent = nullptr) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignCenter);

        QLabel* chessImageLabel = new QLabel(this);
        QPixmap chessImage("C:/Users/user/Desktop/pieces/bK.png"); // Replace with your chess image path
        chessImageLabel->setPixmap(chessImage.scaled(280, 280, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        chessImageLabel->setAlignment(Qt::AlignCenter);
        chessImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(chessImageLabel);

        QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addSpacerItem(spacer);

        QPushButton* startButton = new QPushButton("Start", this);
        startButton->setFixedSize(100, 50);
        startButton->setStyleSheet("font-size: 18px; font-weight: bold; color: white; background-color: #967859; border-radius: 10px;");
        startButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        layout->addWidget(startButton, 0, Qt::AlignCenter);

        // Adding a quit button
        QPushButton* quitButton = new QPushButton("Quit", this);
        quitButton->setFixedSize(100, 50);
        quitButton->setStyleSheet("font-size: 18px; font-weight: bold; color: white; background-color: #967859; border-radius: 10px;");
        quitButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        layout->addWidget(quitButton, 0, Qt::AlignCenter);

        setLayout(layout);
        setStyleSheet("background-color: #D9C3A1;");

        connect(startButton, &QPushButton::clicked, this, &StartGameWindow::openChessBoard);
        // Connect the quit button to the application's quit slot
        connect(quitButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);
    }

signals:
    void startGameClicked();

private slots:
    void openChessBoard() {
        emit startGameClicked();
    }
};


class Controller : public QObject {
private:
    ChessBoardWidget* chessBoard;
    BoardManager boardManager;
    PieceColour playerTurn;
    GameLogic gameLogic;

public:
    Controller() : boardManager(), gameLogic(), playerTurn(PieceColour::White) {}

    void changePlayerTurn() {
        playerTurn = (playerTurn == PieceColour::White) ? PieceColour::Black : PieceColour::White;
    }

    bool isGameOver() {
        bool currentPlayerCanMove = gameLogic.canMove(playerTurn, boardManager);
        bool opponentCanMove = gameLogic.canMove((playerTurn == PieceColour::White) ? PieceColour::Black : PieceColour::White, boardManager);

        if (!currentPlayerCanMove && !opponentCanMove) {
            if (!gameLogic.isInCheck(playerTurn, boardManager)) {
                std::cout << "Stalemate!" << std::endl;
                return true; // Stalemate
            }
        }
        return false; // Game continues
    }

    void startGame() {

    }

};



int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    StartGameWindow startWindow;
    startWindow.resize(420, 420);
    startWindow.show();

    ChessBoardWidget chessboard;
    chessboard.resize(420, 420);

    QObject::connect(&startWindow, &StartGameWindow::startGameClicked, [&chessboard]() {
        chessboard.show();
        chessboard.boardManager_.InitBoard();
        });

    return app.exec();
}

#include "main.moc"
