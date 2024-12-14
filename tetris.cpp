#include "tetris.h"
#include <QHBoxLayout>

Tetris::Tetris(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);  // Основной компоновщик для Tetris

    scorePanel = new ScorePanel(this);
    board = new Board(scorePanel, this);

    layout->addWidget(scorePanel);
    layout->addWidget(board);
    setLayout(layout);  // Устанавливаем компоновку для Tetris

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Tetris::updateGame);

    connect(board, &Board::LevelUp, this, &Tetris::handleLevelUp);

    connect(board, &Board::GameOver, this, &Tetris::resetTimer);

    timer->start(baseSpeed);
}

void Tetris::updateGame()
{
    if (!(board->isPaused))
    {
        board->moveDown();
        board->update();
    }
}

void Tetris::handleLevelUp(int level)
{
    int newSpeed = baseSpeed - (level - 1) * 50;

    if (newSpeed < minSpeed)
    {
        newSpeed = minSpeed;
    }

    qDebug() << "Level up! New speed:" << newSpeed;
    timer->start(newSpeed);
}

void Tetris::resetTimer()
{
    timer->start(baseSpeed);
}