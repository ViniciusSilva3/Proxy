#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    if(argc > 1)
        w.porta = app.arguments().at(1).toInt();
    else
        w.porta = 8228;
    w.show();

    return app.exec();
}
