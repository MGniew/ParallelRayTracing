#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qthread.h"
#include "masterthread.h"
#include "statisticswindow.h"

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
    void on_pushButton_statistics_released();
    void setSpeed(double time);

private:
    Ui::MainWindow *ui;
    StatisticsWindow *statisticWindow;
    MasterThread *masterThread;
};

#endif // MAINWINDOW_H
