#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextBrowser>
#include <QTextStream>
#include <QToolButton>
#include <QGridLayout>
#include <QAbstractButton>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget * wdg = new QWidget(this);
    QGridLayout * vlay = new QGridLayout(wdg);
    QToolButton ** squares = NULL;


    squares = new QToolButton*[64];
    for (int i = 0; i < 64; ++i){
        squares[i] = new QToolButton;
        squares[i]->setMinimumSize(65,65);
        vlay->addWidget(squares[i],i/8,i%8);
    }
    wdg->setLayout(vlay);
    setCentralWidget(wdg);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionUlo_it_jako_triggered()
{
    QString filename = QFileDialog::getSaveFileName(
                this, "Uložit soubor jako", QDir::currentPath(), "Všechny soubory(*.*)");
}

void MainWindow::on_actionUkon_it_triggered()
{

    QMessageBox msgBox;
    msgBox.setText(tr("Opravdu chcete skončit?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Ano"), QMessageBox::YesRole);
    msgBox.addButton(tr("Ne"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==pButtonYes) {
        close();
    }
    else
        return;
}

void MainWindow::on_actionZobrazit_n_pov_du_triggered()
{
    QFile file1("README.txt");
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox msgBox;
        msgBox.critical(this, "Chyba", "Soubor neexistuje!");
        return;
    }

    QTextBrowser *b = new QTextBrowser;
    QTextStream textStream1(&file1);

    b->setWindowIcon(this->windowIcon());
    b->setWindowTitle("Nápověda");
    b->setText(textStream1.readAll());
    b->setMinimumSize(600,500);
    b->show();
}

void MainWindow::on_actionZobrazit_zdroje_triggered()
{
    QTextBrowser *b = new QTextBrowser;

    b->setWindowIcon(this->windowIcon());
    b->setWindowTitle("Zdroje");
    b->setText("Obrázky jsme čerpali z těchto zdrojů:\tPod licencí \nhttp://www.freepik.com \t\tCC 3.0 BY\nhttps://icons8.com\t\tCC BY-ND 3.0");
    b->setMinimumSize(400,100);
    b->show();
}

void MainWindow::on_actionNa_st_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
                this, "Nahrát soubor", QDir::current().currentPath(), "Všechny soubory (*.*)");
}
