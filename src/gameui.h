/*************************************************************
* Project name: hra2016
* File: gameui.h
* Last change: 24.05.2016 17:56
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file gameui.h
*
* @brief Header file for gui gameUI class
* @author Vilem Jelen, Ondrej Molnar
*/

#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>
#include "gameboard.h"
#include "save.h"
#include "ai.h"
#include "core.h"

namespace Ui {
class gameUI;
}

//! Window with graphic elements for playing.
/*!
Draws current state of the game: board, score, turn and enemy type.
Contains buttons for saving game and stepping back and forth in game history.
*/
class gameUI : public QMainWindow
{
    Q_OBJECT

public:
    //! Constructor of gameUI
    /*!
    Creates ui(with its graphical objects).
    Based on params creates GameBoard and other objects.
    \param parent pointer on QWidget
    \param sizeIndex integer with chosen combo box index for board size
    \param enemyIndex integer with chosen combo box index for enemy type
    \param load boolean determining if game needs to be loaded
    \param filename QString contains name of saved game which is going to be loaded
    */
    explicit gameUI(QWidget *parent = 0, int sizeIndex = 1, int enemyIndex = 1, bool load = false, QString filename = "");
    //! Catches key events
    /*!
    Used for keybinds (ESC - closing window)
    \param QKeyEvent
    */
    void keyPressEvent(QKeyEvent *);
    //! Destructor for gameUI
    /*!
    Deletes ui.
    */
    ~gameUI();

private:
    Ui::gameUI *ui;
    // variables used in cli main
    GameBoard * gb = NULL;
    Core * core = new Core();
    Save * save = new Save();
    AI * ai = NULL;
    bool loadResult;
    // message box used for displaing all messages
    QMessageBox msgB;


protected:
    //! Draws board, disks, availables, score, enemy type and who is on turn.
    void paintEvent(QPaintEvent *);
    //! Used for keybinding ESC and closing window
    void mousePressEvent(QMouseEvent * event);
private slots:
    //! Save current game into file on save button click.
    void on_saveBtn_clicked();
    //! Advance in game history on next button click.
    void on_nextBtn_clicked();
    //! Return in game history on back button click.
    void on_backBtn_clicked();
};

#endif // GAMEUI_H

/*** End of file gameui.h ***/
