/*************************************************************
* Project name: hra2016
* File: gameui.cpp
* Last change: 24.05.2016 17:55
*
* Authors:	Vilem Jelen		xjelen09@stud.fit.vutbr.cz
*			Ondrej Molnar	xmolna05@stud.fit.vutbr.cz
*
* Description: Reversi game (othello).
*
***********************************************************/
/**
* @file gameui.cpp
*
* @brief Window for game ui.
* @author Vilem Jelen, Ondrej Molnar
*/

#include "gameui.h"
#include "ui_gameui.h"
#include <QKeyEvent>


gameUI::gameUI(QWidget *parent, int sizeIndex, int enemyIndex, bool load, QString filename) :
    QMainWindow(parent),
    ui(new Ui::gameUI)
{
    ui->setupUi(this);

    // setup message box
    msgB.setWindowTitle("Reversi (Othello)");
    msgB.setWindowIcon(QPixmap(":/reversi.ico"));

    // load saved game
    if (load) {
        // create new game and load data from file
        tie(gb, ai, loadResult) = save->fromFile(core, gb, ai, filename.toStdString());

        if (!loadResult) {
            msgB.setText(" Nepodařilo se načíst hru.\t");
            msgB.exec();
        }
        else {
            gb->setAvailables();
            /*Checking if there are any possible moves*/
            if (gb->noTurn()) {
                gb->nextTurn();
                gb->setAvailables();
                if (gb->noTurn())
                    return;
            }
            repaint();
        }
    }
    // new game
    else {
        // figure out what the size and AI should be
        int size = 8;
        if (sizeIndex == 0) size = 6;
        if (sizeIndex == 2) size = 10;
        if (sizeIndex == 3) size = 12;

        // create new gameboard
        tie(gb, ai) = core->alloc(gb, ai, size, enemyIndex);
        // init save data
        save->setupSave(gb);
        // set available places
        gb->setAvailables();
    }
}

gameUI::~gameUI()
{
    delete ui;
    // delete objects
    tie(gb, ai) = core->destroy(gb, ai);
    delete core;
    delete save;
}

// close game window on escape key
void gameUI::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape)
        close();
}

// put disk on mouse click
void gameUI::mousePressEvent(QMouseEvent *event) {
    // do nothing if its out of gameboard
    if (event->x() < 10 || event->x() > 410 || event->y() < 10 || event->y() > 410)
        return;

    // calculate clicked index
    int size = 400/gb->size;   // size of one square

    int x = (event->x() - 10)/size;
    int y = (event->y() - 10)/size;

    int index = y*gb->size + x;

    if (gb->grid[index] == AVAIL) {
        gb->placeStone(index);
        save->addState(gb);
        gb->setAvailables();
        repaint();

        //Check if game is over
        if (gb->checkEnd()) {
            msgB.setText(" Konec hry.\t");
            msgB.exec();
        }

        //Check if there is no turn
        // + AI code here
        if(gb->enemyAI && !gb->noTurn()) {
            gb->placeStone(ai->run(gb, save));
            save->addState(gb);
            gb->setAvailables();
            repaint();
        }
        //Double check to ensure end after AI plays
        if (gb->checkEnd()) {
            msgB.setText(" Konec hry.\t");
            msgB.exec();
        }
    }
}

// draw gameboard, score, enemy type and turn
void gameUI::paintEvent(QPaintEvent *) {
    // error in game creation
    if (gb == NULL) {
        this->close();
        return;
    }

    QPainter painter(this);
    // use antialiasing
    painter.setRenderHint(QPainter::Antialiasing);

    // pen and brush for blue player
    QBrush player1(QColor(0, 153, 255));
    QPen player1_pen(QColor(0, 45, 179));
    player1_pen.setWidth(2);
    player1_pen.setJoinStyle(Qt::RoundJoin);
    // pen and brush for red player
    QBrush player2(QColor(255, 51, 51));
    QPen player2_pen(Qt::black);
    player2_pen.setWidth(2);
    player2_pen.setJoinStyle(Qt::RoundJoin);
    // brush for available spot
    QBrush avail_brush(QColor(51, 204, 51));
    // rectacle for drawing into grid
    QRect grid_rect;

    QPen pen(Qt::black);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidth(2);

    painter.setPen(pen);

    // size of one square
    int size = 400/gb->size;

    // erase previous drawings
    QRect erase(0, 0, 600, 420);
    painter.eraseRect(erase);


    // main frame around board
    QRect rec(10, 10, gb->size*size, gb->size*size);
    painter.drawRect(rec);

    // draw vertical and horizontal lines
    for (int i = 1; i < gb->size; ++i) {
        painter.drawLine(10 + i*size, 10, 10 + i*size, 10 + gb->size*size);
        painter.drawLine(10, 10 + i*size, 10 + gb->size*size, 10 + i*size);
    }


    // draw disks and availables based on gb->grid[]
    int index = 0;
    for (int k = 0; k < gb->size; ++k) {
        for (int j = 0; j < gb->size; ++j) {
            index = j*gb->size + k;
            if (gb->grid[index] != NONE)
                if (gb->grid[index] != AVAIL) {
                    grid_rect.setRect(14 + k * size, 14 + j * size, size-8, size-8);
                    // draw player1
                    if (gb->grid[index] == WHITE) {
                        painter.setPen(player2_pen);
                        painter.setBrush(player2);
                    }
                    // draw player2
                    else {
                        painter.setPen(player1_pen);
                        painter.setBrush(player1);
                    }
                    painter.drawEllipse(grid_rect);
                }
                else { // position is available
                    grid_rect.setRect(12 + k * size, 12 + j * size, size-4, size-4);;
                    painter.fillRect(grid_rect, avail_brush);
                }
        }
    }

    // draw enemy type
    painter.setFont(QFont("Brandon Grotesque", 12));
    QPen enemy(Qt::black);
    painter.setPen(enemy);
    string enemytext;
    if (gb->getAIType() == 0) enemytext = "Protihráč: Člověk";
    if (gb->getAIType() == 1) enemytext = "Protihráč: Easy AI";
    if (gb->getAIType() == 2) enemytext = "Protihráč: Hard AI";
    painter.drawText(440, 40, enemytext.data());


    // draw who is on turn
    grid_rect.setRect(475, 160, 60, 60);
    if (gb->BlackOnTurn) {
        painter.setPen(player1_pen);
        painter.setBrush(player1);
    }
    else {
        painter.setPen(player2_pen);
        painter.setBrush(player2);
    }
    painter.drawEllipse(grid_rect);


    // draw score
    int b_score, w_score;
    gb->calcScore(b_score, w_score);
    painter.setFont(QFont("Brandon Grotesque", 15, QFont::Bold));
    // blue score
    painter.setPen(player1_pen);
    painter.drawText(450, 110, to_string(b_score).data());
    // red score
    player1_pen.setColor(QColor(255, 51, 51));
    painter.setPen(player1_pen);
    painter.drawText(545, 110, to_string(w_score).data());
}

// save game
void gameUI::on_saveBtn_clicked() {
    // save to file with standard name
    if (save->toFile("")) {
        msgB.setText(" Hra byla úspěšně uložena.\t");
        msgB.exec();
    }
}

// next btn
void gameUI::on_nextBtn_clicked() {
    // one step further in game history
    tie(gb, loadResult) = save->loadState(gb, true);
    if (!loadResult) {
        msgB.setText(" Nelze jít o tah dopředu.\t");
        msgB.exec();
    }
    gb->setAvailables();
    repaint();
    //Check if game is over
    if (gb->checkEnd()) {
        msgB.setText(" Konec hry.\t");
        msgB.exec();
    }
}

// back btn
void gameUI::on_backBtn_clicked() {
    // one step back in game history
    tie(gb, loadResult) = save->loadState(gb, false);
    if (!loadResult) {
        msgB.setText(" Nelze jít o tah zpět.\t");
        msgB.exec();
    }
    gb->setAvailables();
    repaint();
}

/*** End of file gameui.cpp ***/
