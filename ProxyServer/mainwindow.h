#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "proxyserver.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    proxy_server server;
    QString porta;
    QString header1;
    QString header2;
    string msgBrowser;
    string msgfromWeb;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
