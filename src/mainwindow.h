/*************************************************************
* Project name: hra2016
* File: mainwindow.h
* Last change: 24.05.2016 17:56
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
#include "gameui.h"

namespace Ui {
class MainWindow;
}

//! Main window for graphics interface
/*!
Functions as launcher for starting or loading games.
And cointains help dialog.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Constructor of MainWindow
    /*!
    Creates ui(with its graphical objects).
    \param parent pointer on QWidget
    */
    explicit MainWindow(QWidget *parent = 0);
    //! Destructor of MainWindow
    /*!
    Deletes ui.
    */
    ~MainWindow();

private slots:
    //! Close application on exit button click.
    void on_exitBtn_clicked();
    //! Enable/Disable load button based on edited text.
    void on_loadArg_textEdited(const QString &arg1);
    //! Create new game with selected parameters.
    void on_newBtn_clicked();
    //! Load game from file which name is in line edit widget.
    void on_loadBtn_clicked();
    //! Load game from file after pressing enter(return) in line edit.
    void on_loadArg_returnPressed();
    //! Display help dialog on help button click.
    void on_helpBtn_clicked();

private:
    Ui::MainWindow *ui;
    gameUI * boardUi;
};

#endif // MAINWINDOW_H

/*** End of file mainwindow.h ***/
