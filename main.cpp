#include "mainwindow.h"
#include <QApplication>
#include "vector3.h" //temporary tests only
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
