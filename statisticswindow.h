#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QDialog>
#include "mpi.h"
#include "global.h"
#include <string>

namespace Ui {
class StatisticsWindow;
}

class StatisticsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsWindow(QWidget *parent = 0);
    ~StatisticsWindow();
    void resizeEvent(QResizeEvent *event);
    void setTime(double time);
    void setChunks(int i);
    void setXY(int x, int y);
    void setObj(int i);
    void setLights(int i);

public slots:
    void setProccessName(int num, QString str);
    void setProccessSpeed(double **speed);

private:
    Ui::StatisticsWindow *ui;
    void setUpList();
    int worldSize;

};

#endif // STATISTICSWINDOW_H
