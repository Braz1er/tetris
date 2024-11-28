#pragma once
#include <QWidget>
#include <QTimer>
#include "board.h"

class Tetris : public QWidget {
    Q_OBJECT

public:
    Tetris(QWidget *parent = nullptr);

private slots:
    void updateGame();

private:
    Board *board;
    QTimer *timer;
};
