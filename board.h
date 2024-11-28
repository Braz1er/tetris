#pragma once
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <vector>
#include "shape.h"

class Board : public QWidget {
Q_OBJECT

public:
    Board(QWidget *parent = nullptr);
    void moveDown();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void drawSquare(QPainter &painter, int x, int y, QColor color);
    void newPiece();
    bool tryMove(const Shape& shape, int newX, int newY);
    void clearFullLines();

    enum { BoardWidth = 10, BoardHeight = 20 };
    int board[BoardWidth][BoardHeight] = {{0}};
    Shape currentShape;
    int currentX, currentY;
};
