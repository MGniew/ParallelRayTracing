#include "mainwindow.h"
#include <QApplication>
#include "vector3.h" //temporary tests only
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <mpi.h>
#include <stdio.h>

#include <thread>
#include <chrono>

int main(int argc, char *argv[])
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


    if(world_rank == 0) {
        srand(time(NULL));
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }

    printf("rank %d", world_rank);
    MPI_Finalize();
}
