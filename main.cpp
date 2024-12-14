#include <QApplication>
#include "tetris.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Tetris tetris;
    tetris.setFixedSize(450, 640);
    tetris.show();
    return app.exec();
}