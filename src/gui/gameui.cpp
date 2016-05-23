#include "gameui.h"
#include "ui_gameui.h"
#include <QKeyEvent>

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

void gameUI::paintEvent(QPaintEvent *e) {
    QPainter painter(this);

    QPen pen(Qt::blue);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidth(2);

    painter.setPen(pen);

    // size of one square
    int size = 400/gb->size;

    // main frame around board
    QRect rec(10, 10, gb->size*size, gb->size*size);
    painter.drawRect(rec);

    // draw vertical and horizontal lines
    for (int i = 1; i < gb->size; ++i) {
        painter.drawLine(10 + i*size, 10, 10 + i*size, 10 + gb->size*size);
        painter.drawLine(10, 10 + i*size, 10 + gb->size*size, 10 + i*size);
    }

    // draw enemy type


    // draw who is on turn

    // draw score

}
