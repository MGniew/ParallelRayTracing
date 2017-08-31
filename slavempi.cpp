#include "slavempi.h"

SlaveMPI::SlaveMPI()
{   
    int size;
    camera = Camera::getInstance();
    scene = Scene::getInstance();

    //getCamera
    std::vector<char> vec;
    vec.resize(camera->serializedSize);
    MPI_Recv(vec.data(), vec.size(), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    camera->deserialize(vec);

    //getScene
    MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_BYTE, &size);
    vec.resize(size);
    MPI_Recv(vec.data(), size, MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    scene->deserialize(vec);
}

SlaveMPI::~SlaveMPI()
{
    delete scene;
    delete camera;
}

int SlaveMPI::exec()
{
    //while(true)
    {

        //////////////////////////////////////////
        Chunk chunk;
        RayTracer rayTracer;
        std::vector<char> vec;


        while(true) {

        MPI_Recv(&chunk, sizeof(chunk), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        scene->setUpPixels(chunk.stopx - chunk.startx, chunk.stopy - chunk.starty);
        scene->pixels->setStartXY(chunk.startx, chunk.starty);
        rayTracer.recursiveRayTracer(8);
        scene->pixels->serialize(&vec);
        MPI_Send(vec.data(), vec.size(), MPI_BYTE, 0, 2, MPI_COMM_WORLD);
        }

        MPI_Finalize();

    }


    return 0;
}
