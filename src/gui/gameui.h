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

class gameUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameUI(QWidget *parent = 0, int sizeIndex = 1, int enemyIndex = 1, bool load = false, QString filename = "");
    void keyPressEvent(QKeyEvent *);
    ~gameUI();

private:
    Ui::gameUI *ui;
    // variables used in cli main
    GameBoard * gb = NULL;
    Core * core = new Core();
    Save * save = new Save();
    AI * ai = NULL;
    bool loadResult;
    QMessageBox msgB;


protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
private slots:
    void on_saveBtn_clicked();
    void on_nextBtn_clicked();
    void on_backBtn_clicked();
};

#endif // GAMEUI_H
