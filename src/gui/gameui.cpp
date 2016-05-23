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
    // repaint board
    update();
}

gameUI::~gameUI()
{
    delete ui;
}

// close game window on escape key
void gameUI::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape)
        close();
}

void gameUI::paintEvent(QPaintEvent *e) {
    QPainter painter(this);

    QPen pointpen(Qt::black);

    pointpen.setWidth(6);

    QPen linepen(Qt::red);

    linepen.setWidth(2);

    QPoint p1;

    p1.setX(10);
    p1.setY(10);

    QPoint p2;

    p2.setX(100);
    p2.setY(300);

    painter.setPen(linepen);

    painter.drawLine(p1, p2);

    painter.setPen(pointpen);

    painter.drawPoint(p1);
    painter.drawPoint(p2);

    //QRect rect


}
