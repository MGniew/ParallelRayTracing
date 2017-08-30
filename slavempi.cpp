#include "slavempi.h"

SlaveMPI::SlaveMPI()
{
}

int SlaveMPI::exec()
{
    //while(true)
    {
        //temp
        FileLoader fileLoader;
        if(!fileLoader.ReadFile("scene.old.txt")) {
            exit(-1);
        }
        camera = Camera::getInstance();
        scene = Scene::getInstance();
        //////////////////////////////////////////
        MPI_Status status;
        Chunk chunk;
        RayTracer rayTracer;
        ///////////////////////////////////////////////////////////

        while(true) {

        MPI_Recv(&chunk, sizeof(chunk), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        scene->setUpPixels(chunk.stopx - chunk.startx, chunk.stopy - chunk.starty);
        scene->pixels->setStartXY(chunk.startx, chunk.starty);
        rayTracer.recursiveRayTracer(8);
        std::vector<char> vec;
        scene->pixels->serialize(&vec);
        MPI_Send(vec.data(), vec.size(), MPI_BYTE, 0, 2, MPI_COMM_WORLD);
        }

        MPI_Finalize();

    }


    return 0;
}
