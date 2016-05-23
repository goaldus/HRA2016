#include "gameui.h"
#include "ui_gameui.h"
#include <QKeyEvent>
#include <QMessageBox>

gameUI::gameUI(QWidget *parent, int sizeIndex, int enemyIndex) :
    QMainWindow(parent),
    ui(new Ui::gameUI)
{
    ui->setupUi(this);
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

void gameUI::mousePressEvent(QMouseEvent *event) {
    // do nothing if its out of gameboard
    if (event->x() < 10 || event->x() > 410 || event->y() < 10 || event->y() > 410)
        return;

    // calculate clicked index
    int size = 400/gb->size;   // size of one square

    int x = (event->x() - 10)/size;
    int y = (event->y() - 10)/size;

    int index = x*gb->size + y;

    QMessageBox msgBox;

    if (gb->grid[index] == AVAIL) {
        gb->placeStone(index);
        save->addState(gb);
        gb->setAvailables();
        repaint();

        //Check if game is over
        if (gb->checkEnd()) {
            msgBox.setText("Konec hry.");
            msgBox.exec();
        }

        //Check if there is no turn
        // + AI code here
        if(gb->enemyAI && !gb->noTurn()) {
            gb->placeStone(ai->run(gb, save));
            gb->setAvailables();
            repaint();
        }
        //Double check to ensure end after AI plays
        if (gb->checkEnd()) {
            msgBox.setText("Konec hry.");
            msgBox.exec();
        }
    }
}


void gameUI::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

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
            index = k*gb->size + j;
            if (gb->grid[index] != NONE)
                if (gb->grid[index] != AVAIL) {
                    grid_rect.setRect(14 + k * size, 14 + j * size, size-8, size-8);
                    // draw player1
                    if (gb->grid[index] == WHITE) {
                        painter.setPen(player1_pen);
                        painter.setBrush(player1);
                    }
                    // draw player2
                    else {
                        painter.setPen(player2_pen);
                        painter.setBrush(player2);
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


    // draw who is on turn

    // draw score

}
