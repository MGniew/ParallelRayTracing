#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statisticWindow = new StatisticsWindow(this);
    masterThread = new MasterThread;
    connect(masterThread, SIGNAL(workIsReady()), ui->openGLWidget, SLOT(update()));
    connect(masterThread, SIGNAL(setTime(double)), this, SLOT(setSpeed(double)));
    connect(masterThread, SIGNAL(processInfo(double**)), statisticWindow, SLOT(setProccessSpeed(double**)));
    masterThread->start(QThread::HighPriority);
}

MainWindow::~MainWindow()
{
    delete statisticWindow;
    delete ui;
    delete masterThread;
}

void MainWindow::on_pushButton_statistics_released()
{
    if (statisticWindow->isHidden())
        statisticWindow->show();
    else
        statisticWindow->hide();

    ui->pushButton_statistics->addAction(new QAction(nullptr));
}

void MainWindow::setSpeed(double time)
{
    QString string = QString("SPF: %1    FPS: %2").arg(time, 0, 'f', 2).arg(1/time, 0, 'f', 2);
    ui->statusBar->showMessage(string);
    statisticWindow->setTime(time);
}
