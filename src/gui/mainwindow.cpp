#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameui.h"

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

void MainWindow::on_exitBtn_clicked()
{
    QCoreApplication::exit(0);
}

void MainWindow::on_loadArg_textEdited(const QString &arg1)
{
    if (!arg1.isEmpty())
        ui->loadBtn->setDisabled(false);
    else
        ui->loadBtn->setDisabled(true);
}

void MainWindow::on_newBtn_clicked()
{
    boardUi = new gameUI(this, ui->sizeCB->currentIndex(), ui->enemyCB->currentIndex());
    boardUi->show();
}
