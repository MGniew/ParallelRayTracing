#include "statisticswindow.h"
#include "ui_statisticswindow.h"
#include "iostream"

StatisticsWindow::StatisticsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);
}

StatisticsWindow::~StatisticsWindow()
{
    delete ui;
}

void StatisticsWindow::resizeEvent(QResizeEvent *event)
{
    for (int i = 0; i<ui->tableWidget->columnCount(); i++)
        ui->tableWidget->setColumnWidth(i, ui->tableWidget->width()/3 - 1);
}

void StatisticsWindow::setTime(double time)
{
    ui->lineEdit_spf->setText(QString::number(time, 'f', 2));
    ui->lineEdit_fps->setText(QString::number(1/time, 'f', 2));
}

void StatisticsWindow::setChunks(int i)
{
    ui->lineEdit_chunks->setText(QString::number(i));
}

void StatisticsWindow::setXY(int x, int y)
{
    ui->lineEdit_width->setText(QString::number(x));
    ui->lineEdit_height->setText(QString::number(y));
}

void StatisticsWindow::setObj(int i)
{
    ui->lineEdit_obj->setText(QString::number(i));
}

void StatisticsWindow::setLights(int i)
{
    ui->lineEdit_lights->setText(QString::number(i));
}
