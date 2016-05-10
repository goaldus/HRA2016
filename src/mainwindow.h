/*************************************************************
* Project name: HRA2016
* File: mainwindow.h
* Last change: 09.05.2016 01:13
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file mainwindow.h
*
* @brief Header file for gui MainWindow class
* @author Vilem Jelen, Ondrej Molnar
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionUlo_it_jako_triggered();

    void on_actionUkon_it_triggered();

    void on_actionZobrazit_n_pov_du_triggered();

    void on_actionZobrazit_zdroje_triggered();

    void on_actionNa_st_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

/*** End of file mainwindow.h ***/
