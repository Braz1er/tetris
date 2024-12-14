#pragma once

#include <QWidget>
#include <QTimer>
#include "board.h"
#include "scorepanel.h"

class Tetris : public QWidget {
    Q_OBJECT

public:
    Tetris(QWidget *parent = nullptr);

private slots:
    void updateGame();
    void handleLevelUp(int level);
    void resetTimer();

private:
    Board *board;
    QTimer *timer;
    ScorePanel *scorePanel;

    int baseSpeed = 500;
    int minSpeed = 100;
};