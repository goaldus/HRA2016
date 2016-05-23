#ifndef GAMEUI_H
#define GAMEUI_H

#include <QMainWindow>
#include <QtGui>
#include "gameboard.h"
#include "save.h"
#include "ai.h"
#include "core.h"

namespace Ui {
class gameUI;
}

class gameUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameUI(QWidget *parent = 0, int sizeIndex = 1, int enemyIndex = 1);
    void keyPressEvent(QKeyEvent *);
    ~gameUI();

private:
    Ui::gameUI *ui;
    // variables used in cli main
    GameBoard * gb;
    Core * core = new Core();
    Save * save = new Save();
    AI * ai;
    bool loadResult;


protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent * event);
};

#endif // GAMEUI_H
