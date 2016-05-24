#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameui.h"
#include <QMessageBox>

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

void MainWindow::on_loadBtn_clicked()
{
    boardUi = new gameUI(this, 0, 0, true, ui->loadArg->text());
    boardUi->show();
}

void MainWindow::on_loadArg_returnPressed()
{
    boardUi = new gameUI(this, 0, 0, true, ui->loadArg->text());
    boardUi->show();
}

void MainWindow::on_helpBtn_clicked()
{
    QMessageBox box;
    QString help;
    help += "<div align='justify'>Reversi (Othello) je desková hra pro dva hráče.<br>"
            "Hráči na desku pokládají kameny, "
            "které jsou z jedné strany modré a z druhé červené, tak, aby mezi "
            "právě položený kámen a jiný kámen své barvy uzavřeli souvislou "
            "řadu soupeřových kamenů. Tyto kameny se potom otočí a stanou se "
            "kameny druhého hráče.<br> Vítězí hráč, který má na konci hry více svých kamenů.<br></div>";

    help += "Klávesové zkratky:<div style='margin-left: 20px; margin-top:7px;'>"
            "<pre>Nová hra                        C<br>"
            "Načíst uloženou hru             L<br>"
            "Uložit hru                      S<br>"
            "Tah zpět                        B<br>"
            "Tah dopředu                     N<br>"
            "Nápověda                        F1<br>"
            "Ukončit                         ESC<br></pre></div>";

    help += "<p>Autoři: Vilém Jelen a Ondřej Molnár<br>24.května 2016</p>";
    box.setFont(QFont("Brandon Grotesque"));
    box.about(ui->centralWidget, "Nápověda", help);
}
