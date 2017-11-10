#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    statisticWindow = new StatisticsWindow(this);
    createMaster();
    connect(masterThread, SIGNAL(workIsReady()), ui->openGLWidget, SLOT(update()));
    connect(masterThread, SIGNAL(setTime(double)), this, SLOT(setSpeed(double)));
    connect(masterThread, SIGNAL(processInfo(double**)), statisticWindow, SLOT(setProccessSpeed(double**)));
    connect(masterThread, SIGNAL(close()), this, SLOT(onQuit()));
    masterThread->start(QThread::HighPriority);

    statisticWindow->setXY(Camera::getInstance()->getPixWidth(),
                           Camera::getInstance()->getPixHeight());
    statisticWindow->setChunks(masterThread->getNumOfChunks());
    statisticWindow->setObj(Scene::getInstance()->getNumOfObjects());

    statisticWindow->setLights(Scene::getInstance()->getNumOfLights());
}

MainWindow::~MainWindow()
{
    delete statisticWindow;
    delete ui;
    delete masterThread;
}

void MainWindow::ShowStats()
{
    if (statisticWindow->isHidden())
        statisticWindow->show();
    else
        statisticWindow->hide();
}

void MainWindow::setSpeed(double time)
{
    QString string = QString("SPF: %1    FPS: %2").arg(time, 0, 'f', 2).arg(1/time, 0, 'f', 2);
    ui->statusBar->showMessage(string);
    statisticWindow->setTime(time);
}

void MainWindow::on_actionStatistics_triggered()
{
    ShowStats();
}

void MainWindow::onQuit()
{
    this->close();
}

void MainWindow::createMaster()
{
    QStringList list = QCoreApplication::arguments();
    InputParser parser(list);

    std::string file;
    std::string value;
    int width = 700, height = 500, chunks = 10, depth = 3, test = 0;
    bool shadows = false, bsp = false;

    if (parser.cmdOptionExists("-s")) {
        shadows = true;
    }

    if (parser.cmdOptionExists("-b")) {
        bsp = true;
    }

    file = parser.getCmdOption("-f");
    if (file.empty()) {
        file = "scene.old.txt";
    }

    value = parser.getCmdOption("-w");
    if (!value.empty()) {
        width = std::stoi(value);
        if (width < 0) width = 0;
    }

    value = parser.getCmdOption("-h");
    if (!value.empty()) {
        height = std::stoi(value);
        if (height < 0) height = 0;
    }

    value = parser.getCmdOption("-c");
    if (!value.empty()) {
        chunks = std::stoi(value);
        if (chunks < 1) chunks = 1;
    }

    value = parser.getCmdOption("-d");
    if (!value.empty()) {
        depth = std::stoi(value);
        if (depth < 1) depth = 1;
    }

    value = parser.getCmdOption("-t");
    if (!value.empty()) {
        test = std::stoi(value);
        if (test < 0) test = 0;
    }



    masterThread = new MasterThread(file, width, height, chunks, depth, bsp, shadows, test);
}


