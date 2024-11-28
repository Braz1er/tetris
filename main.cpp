#include <QApplication>
#include "tetris.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Tetris tetris;
    tetris.setFixedSize(300, 600);  // Размер игрового окна
    tetris.show();
    return app.exec();
}
