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
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    start(HighPriority);

}

MasterThread::~MasterThread()
{
    isAlive = false;
    wait();
    delete scene;
    delete camera;

  //  MPI_Abort(MPI_COMM_WORLD, 0);
   // MPI_Finalize();

}

void MasterThread::splitToChunks(int num) {

    clearQueue(queue);

    Camera* camera = Camera::getInstance();
    int chunksx = camera->getPixWidth()/num;
    int chunksy = camera->getPixHeight()/num;

    Chunk chunk;
    chunk.startx = 0;
    chunk.starty = 0;

    for(int i=1; i<=num; i++) {
        if (i == num) chunk.stopx = camera->getPixWidth();
        else chunk.stopx = chunk.startx + chunksx;
        chunk.starty = 0;
        for(int j=1; j<=num; j++){
            if (j==num) chunk.stopy = camera->getPixHeight();
            else chunk.stopy = chunk.starty + chunksy;
            queue.push(chunk);
            chunk.starty = chunk.stopy;
        }
        chunk.startx = chunk.stopx;
    }
}

void MasterThread::clearQueue(std::queue<Chunk> &q)
{
    std::queue<Chunk> empty;
    std::swap(q,empty);
}

void MasterThread::run()
{
    MPI_Status status;
    std::vector<char> vec;
    int size;
    int numChunks = 10;
    splitToChunks(numChunks);
    numChunks *= numChunks;

    vec.resize(camera->serializedSize);
    camera->serialize(&vec);
    for(int i=1; i<worldSize; i++) {
        MPI_Send(vec.data(), vec.size(), MPI_BYTE, i, 5, MPI_COMM_WORLD);
    }

    vec.resize(scene->serializedSize);
    scene->serialize(&vec);
    for(int i=1; i<worldSize; i++) {
        MPI_Send(vec.data(), vec.size(), MPI_BYTE, i, 5, MPI_COMM_WORLD);
    }



    int i = 1;
    Chunk chunk;
    while(!queue.empty() && i<worldSize) {
        chunk = queue.front();
        queue.pop();
        MPI_Send(&chunk, sizeof(chunk), MPI_BYTE, i, 1, MPI_COMM_WORLD);
        i++;
    }


    int flag = 0;
    while(numChunks>0) {
        while(!flag) {
            MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
            if (!isAlive) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        if (!isAlive) break;
        //MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_BYTE, &size);
        vec.resize(size);
        MPI_Recv(vec.data(), size, MPI_BYTE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        scene->pixels->deserialize(vec);


        if(!queue.empty()) {
            chunk = queue.front();
            queue.pop();
            MPI_Send(&chunk, sizeof(chunk), MPI_BYTE, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
        }
        numChunks--;
        emit workIsReady();
    }

    emit workIsReady();

//    while(isAlive)
//    {

//    }
}
