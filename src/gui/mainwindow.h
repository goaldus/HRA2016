#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameui.h"

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
    void on_exitBtn_clicked();

    void on_loadArg_textEdited(const QString &arg1);

    void on_newBtn_clicked();

    void on_loadBtn_clicked();

    void on_loadArg_returnPressed();

private:
    Ui::MainWindow *ui;
    gameUI * boardUi;
};

#endif // MAINWINDOW_H
