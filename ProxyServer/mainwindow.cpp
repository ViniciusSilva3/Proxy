#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    msgfromWeb = server.enviaBrowser(msgBrowser);
    qDebug() << "lol";
}



void MainWindow::on_pushButton_4_clicked()
/* Open connection button */
{
    qDebug() << "Button pressed";
    server = proxy_server();
    server.start();
    msgBrowser = server.abreConexaoBrowser();
    ui->textEdit->setPlainText(msgBrowser.c_str());
}
