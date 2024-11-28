#include "tetris.h"
#include <QVBoxLayout>

Tetris::Tetris(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);  // Основной компоновщик для Tetris
    board = new Board(this);
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
