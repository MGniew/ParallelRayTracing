#include "masterthread.h"

MasterThread::MasterThread(QObject *parent) : QThread(parent)
{
    isAlive = true;
    FileLoader fileLoader;
    if(!fileLoader.ReadFile("scene.old.txt")) {
        exit(-1);
    }
    camera = Camera::getInstance();
    scene = Scene::getInstance();


    start(HighPriority);

}

MasterThread::~MasterThread()
{
    isAlive = false;
    wait();
    delete scene;
    delete camera;
    MPI_Finalize();

}

void MasterThread::run()
{

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d"
           " out of %d processors\n",
           processor_name, world_rank, world_size);


    Vector3<float> a(0.3, 0.2, 0.1);
    std::vector<char> vec;
    a.serialize(&vec);

    for(int i=1; i<world_size; i++) {
       MPI_Send(vec.data(), vec.size(), MPI_BYTE, i, 666, MPI_COMM_WORLD);
    }


    RayTracer rayTracer;
    rayTracer.recursiveRayTracer(2);
    emit workIsReady();

//    while(isAlive)
//    {

//    }
}
