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

    sendCamera();
    sendScene();
    sendDepth(3);
    numChunks=10;

    processSpeed = new double*[worldSize];
    for(int i = 0; i< worldSize; i++) {
        processSpeed[i] = new double[3];
        processSpeed[i][0] = 0;
        processSpeed[i][1] = 0;
    }

}

MasterThread::~MasterThread()
{
    isAlive = false;
    std::cout << "exiting..." << std::endl;
    wait();
    finishPending();
    sendExitSignal();
    delete scene;
    delete camera;
    for(int i = 0; i< worldSize; i++)
        delete [] processSpeed[i];
    delete [] processSpeed;
    MPI_Finalize();
}

int MasterThread::getNumOfChunks()
{
    return numChunks*numChunks;
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

void MasterThread::sendCamera()
{
    std::vector<char> vec;
    vec.resize(camera->serializedSize);
    camera->serialize(&vec);
    MPI_Bcast(vec.data(), vec.size(), MPI_BYTE, 0, MPI_COMM_WORLD);
}

void MasterThread::sendScene() {

    int size;
    std::vector<char> vec;
    size = scene->serializedSize;
    vec.resize(size);
    scene->serialize(&vec);
    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(vec.data(), vec.size(), MPI_BYTE, 0, MPI_COMM_WORLD);

}

void MasterThread::sendDepth(int depth) {
    MPI_Bcast(&depth, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

bool MasterThread::sendNextChunk(int dest) {

     if (queue.empty()) {
         return false;
     }

     Chunk chunk;
     chunk = queue.front();
     queue.pop();
     MPI_Send(&chunk, sizeof(chunk), MPI_BYTE, dest, CHUNK, MPI_COMM_WORLD);
     return true;
}

void MasterThread::sendExitSignal()
{
    for(int i=1;i<worldSize;i++)
        MPI_Send(nullptr, 0, MPI_BYTE, i, EXIT, MPI_COMM_WORLD);
}

int MasterThread::recvPixels(MPI_Status &status)
{
    int size;
    std::vector<char> vec;
    MPI_Get_count(&status, MPI_BYTE, &size);
    vec.resize(size);
    MPI_Recv(vec.data(), size, MPI_BYTE, MPI_ANY_SOURCE, PIXELS, MPI_COMM_WORLD, &status);
    scene->pixels->deserialize(vec);
    return status.MPI_SOURCE;
}

int MasterThread::recvMessage()
{
    int flag = 0;
    while(!flag) {
        MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
        if (!isAlive) return EXIT;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return PIXELS;

}

void MasterThread::finishPending()
{
    while(pending>0) {
        MPI_Probe(MPI_ANY_SOURCE, PIXELS, MPI_COMM_WORLD, &status);
        recvPixels(status);
        pending--;
    }

}

void MasterThread::updateProcessSpeed()
{
    double chunkTime;
    chunkTime = MPI_Wtime();
    processSpeed[status.MPI_SOURCE][0]++;
    processSpeed[status.MPI_SOURCE][1] += chunkTime - processSpeed[status.MPI_SOURCE][2];
    processSpeed[status.MPI_SOURCE][2] = chunkTime;
}

void MasterThread::run()
{
    RayTracer raytracer;
    raytracer.recursiveRayTracer(3);

//    double t1, t2;
//    splitToChunks(numChunks);

//    t1 = MPI_Wtime();
//    pending = 0;
//    for (int i=1; i<worldSize; i++) {
//        if (!sendNextChunk(i)) break;
//        processSpeed[i][2] = MPI_Wtime();
//        pending++;
//    }


//    int dest;

//    while(pending>0) {

//        switch(recvMessage()) {
//            case EXIT: return; break;
//            case PIXELS:
//                dest = recvPixels(status);
//                updateProcessSpeed();
//                if (!sendNextChunk(dest))
//                    pending--;
//                break;
//            default: break;
//        }
//       // emit workIsReady();
//        emit processInfo(processSpeed);
//    }
//    t2 = MPI_Wtime();


//    emit setTime(t2-t1);
    emit workIsReady();

    recvMessage(); //temp

}
