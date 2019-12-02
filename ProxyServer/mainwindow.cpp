#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resposta.h"
#include "requisicao.h"
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
    /* manda a mensagem para o servidor web, podendo
     * ter alterado a requisicao get feita pelo
     * browser */
    /* para pegar a string da caixa de texto editada */
    QString   texto = ui->textEdit->toPlainText();
    texto.replace("\n", "\r\n");

    qDebug() << "Criou o novo text";

    // repassa para o servidor web
    msgfromWeb = server.enviaBrowser(msgBrowser);
        qDebug() << "nao chega";

    ui->textEdit_2->setPlainText(msgfromWeb.c_str());
    Resposta rs = Resposta(msgfromWeb);
    msgfromWeb = rs.montaRes();

    qDebug() << "lol";
}



void MainWindow::on_pushButton_4_clicked()
/* Open connection button */
{
    qDebug() << "Button pressed";
    server = proxy_server();
    server.start(porta);
    msgBrowser = server.abreConexaoBrowser();
    ui->textEdit->setPlainText(msgBrowser.c_str());
}

void MainWindow::on_pushButton_2_clicked()
{
    /* pega o texto recebido do servidor web
     * depois de ter sido alterado
     * e devolve para o browser */
    QString texto = ui->textEdit_2->toPlainText();
    texto.replace("\n", "\r\n");
    msgfromWeb   = texto.toUtf8().constData();
    server.respostaParaBrowser(msgfromWeb);

}

void MainWindow::on_pushButton_3_clicked()
{
    /* Limpa as caixas de texto */
    ui->textEdit_2->clear();
    ui->textEdit->clear();
}
