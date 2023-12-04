#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include "Includes.hpp"
#include "QtIncludes.hpp"
#include "Definitions.hpp"

class GameWindow : public QWidget {
    Q_OBJECT

public:
    GameWindow(QWidget* parent = nullptr) : QWidget(parent);

signals:
    void startGameClicked();

private slots:
    void openChessBoard();
};

#emdif
