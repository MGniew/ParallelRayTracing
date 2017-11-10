#include "mainwindow.h"
#include <QApplication>
#include "vector3.h" //temporary tests only
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <mpi.h>
#include <stdio.h>

#include "slavempi.h"
#include "inputparser.h"

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);



    if(world_rank == 0) {
        srand(time(NULL));
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }

    SlaveMPI slave;
    return slave.exec();
}
