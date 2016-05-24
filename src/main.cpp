/*************************************************************
* Project name: hra2016
* File: main.cpp
* Last change: 24.05.2016 17:54
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file main.cpp
*
* @brief Main function for gui application
* @author Vilem Jelen, Ondrej Molnar
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*** End of file main.cpp ***/
