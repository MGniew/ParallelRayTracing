#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QDialog>
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


private:
    Ui::StatisticsWindow *ui;

};

#endif // STATISTICSWINDOW_H
