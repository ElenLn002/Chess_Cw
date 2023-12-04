#include "GameWindow.hpp"

GameWindow:: GameWindow(QWidget* parent = nullptr) : QWidget(parent) {
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

    connect(startButton, &QPushButton::clicked, this, &GameWindow::openChessBoard);
    // Connect the quit button to the application's quit slot
    connect(quitButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);
}
