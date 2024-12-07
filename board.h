#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <vector>
#include "shape.h"
#include "scorepanel.h"

class Board : public QWidget {
Q_OBJECT

public:
    Board(ScorePanel *scorePanel, QWidget *parent = nullptr);
    void moveDown();
    void restartGame();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void drawSquare(QPainter &painter, int x, int y, QColor color);
    void newPiece();
    bool tryMove(const Shape& shape, int newX, int newY);
    void clearFullLines();
    void increaseLevel();
    void pauseGame();
    void resumeGame();
    void updateScore(int points);

    enum { BoardWidth = 10, BoardHeight = 20 };
    int board[BoardWidth][BoardHeight] = {{0}};
    Shape currentShape;
    int currentX, currentY;
    int score = 0;
    int level = 1;
    bool isGameOver = false;
    bool isPaused = false;

    ScorePanel *scorePanel;
};
