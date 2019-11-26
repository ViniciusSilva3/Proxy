#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.porta = app.arguments().at(1);
    w.show();

    return app.exec();
}
