#include "statisticswindow.h"
#include "ui_statisticswindow.h"
#include "iostream"

StatisticsWindow::StatisticsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);
    setUpList();
    getNames();
    ui->lineEdit_proc->setText(QString::number(worldSize));
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

void StatisticsWindow::setProccessSpeed(double **speed)
{
    QTableWidgetItem *item;
    double avg;
    for(int i=1; i<worldSize; i++) {
        if (speed[i][0] != 0) {
            avg = speed[i][1]/speed[i][0];
            item = new QTableWidgetItem(tr("%1").arg(avg, 0, 'f', 3));
        }
        else
            item = new QTableWidgetItem("inf");

        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 2, item);
    }
}

void StatisticsWindow::getNames()
{
    char buff[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;

    for (int i=1; i<worldSize; i++) {
        MPI_Recv(buff, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, MPI_ANY_SOURCE, myGlobals::NAME, MPI_COMM_WORLD, &status);
        QString myString = QString::fromUtf8(buff);
        setProccessName(status.MPI_SOURCE, myString);
    }
}

void StatisticsWindow::setUpList()
{
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    ui->tableWidget->setRowCount(worldSize);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    QTableWidgetItem *item;

    item = new QTableWidgetItem("0");
        ui->tableWidget->setItem(0, 0, item);
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        item->setTextAlignment(Qt::AlignCenter);

    item = new QTableWidgetItem("master");
        ui->tableWidget->setItem(0, 1, item);
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        item->setTextAlignment(Qt::AlignCenter);

    item = new QTableWidgetItem("-");
        ui->tableWidget->setItem(0, 2, item);
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        item->setTextAlignment(Qt::AlignCenter);


}

void StatisticsWindow::setProccessName(int num, QString str)
{
    QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(num));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(num, 0, item);


    item = new QTableWidgetItem(str);
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(num, 1, item);
}

