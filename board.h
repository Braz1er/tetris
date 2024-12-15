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
    void pauseGame();
    void increaseLevel();

    bool isPaused = false;

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void LevelUp(int level);
    void GameOver();

private:
    void drawSquare(QPainter &painter, int x, int y, QColor color);
    void newPiece();
    bool tryMove(const Shape& shape, int newX, int newY);
    void clearFullLines();
    void updateScore(int points);
    void drawGrid(QPainter &painter);

    enum { BoardWidth = 10, BoardHeight = 20 };
    int board[BoardWidth][BoardHeight] = {{0}};
    static const int BlockSize = 30;
    Shape currentShape;
    int currentX, currentY;
    int score = 0;
    int level = 1;
    bool isGameOver = false;
    QColor gridColor = QColor(0, 0, 0, 50);

    ScorePanel *scorePanel;
};