#include "slavempi.h"


SlaveMPI::SlaveMPI()
{   
    camera = Camera::getInstance();
    scene = Scene::getInstance();
    recvCamera();
    recvScene();
    recvDepth();
}

SlaveMPI::~SlaveMPI()
{
    MPI_Finalize();
    delete scene;
    delete camera;
}

int SlaveMPI::exec()
{
    RayTracer rayTracer;
    while(true) {

        switch(recvMessage()) {
            case EXIT:
                return EXIT; break;
            case CHUNK:
                recvChunk();
                rayTracer.recursiveRayTracer(depth);
                sendPixels(); break;
            case DEPTH:
                recvDepth(); break;
            default: break;
        }
    }
    return 0;
}

void SlaveMPI::recvCamera()
{
    std::vector<char> vec;
    vec.resize(camera->serializedSize);
    MPI_Bcast(vec.data(), vec.size(), MPI_BYTE, 0, MPI_COMM_WORLD);
    camera->deserialize(vec);
}

void SlaveMPI::recvScene()
{
    int size;
    std::vector<char> vec;
    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    vec.resize(size);
    MPI_Bcast(vec.data(), vec.size(), MPI_BYTE, 0, MPI_COMM_WORLD);
    scene->deserialize(vec);
}

int SlaveMPI::recvMessage()
{
    MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    return status.MPI_TAG;
}

void SlaveMPI::sendPixels()
{
    std::vector<char> vec;
    scene->pixels->serialize(&vec);
    MPI_Send(vec.data(), vec.size(), MPI_BYTE, 0, PIXELS, MPI_COMM_WORLD);
}

void SlaveMPI::recvDepth()
{
    MPI_Bcast(&depth, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

void SlaveMPI::recvChunk()
{
    Chunk chunk;
    MPI_Recv(&chunk, sizeof(chunk), MPI_BYTE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    scene->setUpPixels(chunk.stopx - chunk.startx, chunk.stopy - chunk.starty);
    scene->pixels->setStartXY(chunk.startx, chunk.starty);
}
