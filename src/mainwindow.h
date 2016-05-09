#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_actionUlo_it_jako_triggered();

    void on_actionUkon_it_triggered();

    void on_actionZobrazit_n_pov_du_triggered();

    void on_actionZobrazit_zdroje_triggered();

    void on_actionNa_st_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
