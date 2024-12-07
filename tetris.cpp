#include "tetris.h"
#include <QHBoxLayout>

Tetris::Tetris(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);  // Основной компоновщик для Tetris

    scorePanel = new ScorePanel(this);
    board = new Board(scorePanel, this);

    layout->addWidget(scorePanel);
    layout->addWidget(board);  // Добавляем Board на основной виджет
    setLayout(layout);  // Устанавливаем компоновку для Tetris

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Tetris::updateGame);
    timer->start(300);  // Интервал падения фигур
}

void Tetris::updateGame() {
    board->moveDown();
    board->update();  // Обновление экрана для отрисовки
}
