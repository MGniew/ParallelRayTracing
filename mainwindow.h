#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qthread.h"
#include "masterthread.h"
#include "statisticswindow.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "inputparser.h"
#include "qcoreapplication.h"
#include "QStringList"

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
    void ShowStats();
    void setSpeed(double time);

    void on_actionStatistics_triggered();

private:
    Ui::MainWindow *ui;
    StatisticsWindow *statisticWindow;
    MasterThread *masterThread;
    QLabel* statusLabel;
    void createMaster();
};

#endif // MAINWINDOW_H
