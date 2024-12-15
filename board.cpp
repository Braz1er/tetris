#include "board.h"
#include "shape.h"
#include <QPainter>
#include <QDebug>

Board::Board(ScorePanel *scorePanel, QWidget *parent) : QWidget(parent), scorePanel(scorePanel)
{
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(BoardWidth * 30, BoardHeight * 30);
    restartGame();
}

void Board::restartGame()
{
    currentShape = Shape::randomShape();
    currentX = BoardWidth / 2;
    currentY = 0;

    for (int x = 0; x < BoardWidth; x++)
    {
        for (int y = 0; y < BoardHeight; y++)
        {
            board[x][y] = 0;
        }
    }

    score = 0;
    level = 1;
    isGameOver = false;
    isPaused = false;
    scorePanel->setScore(score);
    scorePanel->setLevel(level);
    newPiece();
}

void Board::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::lightGray);
    drawGrid(painter);

    // Отрисовка уже зафиксированных блоков
    for (int x = 0; x < BoardWidth; x++)
    {
        for (int y = 0; y < BoardHeight; y++)
        {
            if (board[x][y])
            {
                drawSquare(painter, x * 30, y * 30, Qt::blue);
            }
        }
    }

    // Отрисовка текущей падающей фигуры
    for (const auto& block : currentShape.blocks())
    {
        int x = currentX + block[0];
        int y = currentY + block[1];

        if (y >= 0)
        {
            drawSquare(painter, x * 30, y * 30, Qt::red);
        }
    }

    if (isPaused)
    {
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 24, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "PAUSE");
    }
}


void Board::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_P || event->key() == Qt::Key_Space)
    {
        pauseGame();
        update();
        return;
    }

    if (isPaused)
    {
        return;
    }

    switch (event->key())
    {
        case Qt::Key_R:
        {
            restartGame();
            update();
            break;
        }

        case Qt::Key_Left:
        {
            tryMove(currentShape, currentX - 1, currentY);
            update();
            break;
        }

        case Qt::Key_Right:
        {
            tryMove(currentShape, currentX + 1, currentY);
            update();
            break;
        }

        case Qt::Key_Down:
        {
            moveDown();
            update();
            break;
        }

        case Qt::Key_Up:
        {
            int minX, maxX;

            if (currentShape.type() == ShapeType::I)
            {
                minX = 2;
                maxX = -2;
            }
            else
            {
                minX = 1;
                maxX = -1;
            }

            for (const auto &block: currentShape.blocks())
            {
                if (block[0] < minX)
                {
                    minX = block[0];
                }

                if (block[0] > maxX)
                {
                    maxX = block[0];
                }
            }

            if (currentX - minX <= 1)
            {
                if (currentShape.type() == ShapeType::I)
                {
                    currentX = currentX + 3;
                }
                else
                {
                    currentX = currentX + 2;
                }
                qDebug() << "Fixed rotate left";
            }

            if (currentX + maxX >= 9)
            {
                if (currentShape.type() == ShapeType::I)
                {
                    currentX = currentX - 3;
                }
                else
                {
                    currentX = currentX - 2;
                }
                qDebug() << "Fixed rotate right";
            }

            currentShape.rotate();
            tryMove(currentShape, currentX, currentY);
            update();
            break;
        }
    }
}

void Board::moveDown()
{
    if (!tryMove(currentShape, currentX, currentY + 1))
    {
        for (const auto& block : currentShape.blocks())
        {
            int x = currentX + block[0];
            int y = currentY + block[1];

            if (y >= 0)
            {
                board[x][y] = 1;
            }
        }

        clearFullLines();
        clearFullLines();
        clearFullLines();
        clearFullLines();
        newPiece();
    }
    update();
}

void Board::drawSquare(QPainter &painter, int x, int y, QColor color)
{
    painter.setBrush(color);
    painter.drawRect(x, y, 30, 30);
}

void Board::newPiece()
{
    currentShape = Shape::randomShape();
    currentX = BoardWidth / 2;
    currentY = 0;

    if (!tryMove(currentShape, currentX, currentY))
    {
        // Конец игры, если новая фигура не может быть размещена
        for (int x = 0; x < BoardWidth; x++)
        {
            for (int y = 0; y < BoardHeight; y++)
            {
                board[x][y] = 0;  // Очистка поля
            }
        }

        score = 0;
        level = 1;

        scorePanel->setScore(score);
        scorePanel->setLevel(level);

        emit GameOver();
    }
}

bool Board::tryMove(const Shape& shape, int newX, int newY)
{
    for (const auto& block : shape.blocks())
    {
        int x = newX + block[0];
        int y = newY + block[1];

        if (x < 0 || x >= BoardWidth || y >= BoardHeight || (y >= 0 && board[x][y]))
        {
            return false;
        }
    }

    currentX = newX;
    currentY = newY;
    return true;
}

void Board::clearFullLines()
{
    for (int y = BoardHeight - 1; y >= 0; y--)
    {
        bool full = true;

        for (int x = 0; x < BoardWidth; x++)
        {
            if (!board[x][y])
            {
                full = false;
                break;
            }
        }

        if (full)
        {
            updateScore(100);

            for (int yy = y; yy > 0; yy--)
            {
                for (int x = 0; x < BoardWidth; x++)
                {
                    board[x][yy] = board[x][yy - 1];
                }
            }
        }
    }
}

void Board::updateScore(int points)
{
    score += points;
    scorePanel->setScore(score);

    if (score % 500 == 0)
    {
        increaseLevel();
    }
}

void Board::increaseLevel()
{
    level++;
    scorePanel->setLevel(level);
    emit LevelUp(level);
}

void Board::pauseGame()
{
    if (isGameOver)
    {
        return;
    }

    isPaused = !isPaused;
}

void Board::drawGrid(QPainter &painter)
{
    QPen pen(gridColor);
    pen.setWidth(1);
    painter.setPen(pen);

    // Вертикальные линии
    for (int x = 0; x <= BoardWidth; x++)
    {
        int xPos = x * BlockSize;
        painter.drawLine(xPos, 0, xPos, BoardHeight * BlockSize);
    }

    // Горизонтальные линии
    for (int y = 0; y <= BoardHeight; y++)
    {
        int yPos = y * BlockSize;
        painter.drawLine(0, yPos, BoardWidth * BlockSize, yPos);
    }
}