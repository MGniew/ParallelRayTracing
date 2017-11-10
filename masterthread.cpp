#include "masterthread.h"


MasterThread::MasterThread(std::string file, int width, int height, int chunks, int depth, bool bsp, bool shadows, int test, QObject *parent) : QThread(parent)
{
    isAlive = true;
    FileLoader fileLoader;
    std::cout << file << std::endl;
    if(!fileLoader.ReadFile(file.c_str())) {
        exit(-1);
    }
    camera = Camera::getInstance();
    camera->setUp(width, height);

    scene = Scene::getInstance();
    scene->setUpPixels(width, height);
    scene->setBSPUsage(bsp);
    scene->setShadowsUsage(shadows);

    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    getNames();
    sendCameraBcast();
    sendScene();
    sendDepth(depth);
    numChunks=chunks;
    this->test = test;

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

void MasterThread::sendCameraBcast()
{
    std::vector<char> vec;
    vec.resize(camera->serializedSize);
    camera->serialize(&vec);
    MPI_Bcast(vec.data(), vec.size(), MPI_BYTE, 0, MPI_COMM_WORLD);
}


void MasterThread::sendCameraPointToPoint()
{
    for (int i = 1; i < worldSize; i++) {
        std::vector<char> vec;
        vec.resize(camera->serializedSize);
        camera->serialize(&vec);
        MPI_Send(vec.data(), vec.size(), MPI_BYTE, i, CAMERA, MPI_COMM_WORLD);
    }
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

void MasterThread::waitUntillRdy()
{
    for(int i = 1; i< worldSize; i++) {
        MPI_Recv(nullptr, 0, MPI_BYTE, MPI_ANY_SOURCE, READY, MPI_COMM_WORLD, &status);
    }
}

void MasterThread::printResult(double spf, double bsp)
{
    Scene* scene = Scene::getInstance();
    Camera* camera = Camera::getInstance();

    std::cout << "Objets: " << scene->getNumOfObjects() << std::endl;
    std::cout << "Lights: " << scene->getNumOfLights() << std::endl;
    std::cout << "width|height: " << camera->getPixWidth() << "|" << camera->getPixHeight() << std::endl;
    if (scene->useBSP) {
        std::cout << "BSP: " << bsp << std::endl;
    }
    std::cout << "Shadows: " << scene->useShadows << std::endl;
    std::cout << "fps|spf: " << 1/spf << "|" << spf << std::endl;
    for (int i = 1; i < worldSize; i++) {
        std::cout << i << " " << names[i] << ": " << processSpeed[i][1]/processSpeed[i][0] << std::endl;
    }


}

void MasterThread::getNames()
{
    char buff[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;
    names.resize(worldSize);
    names[0] = "master";

    for (int i=1; i<worldSize; i++) {
        MPI_Recv(buff, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, MPI_ANY_SOURCE, myGlobals::NAME, MPI_COMM_WORLD, &status);
        names[status.MPI_SOURCE] = std::string(buff);
    }
}

void MasterThread::emitNames()
{
    for (int i = 1; i < worldSize; i++)
        emit setName(i, QString::fromStdString(names[i]));
}

void MasterThread::run()
{
    double time = 0; double bsp = 0;
    int n = test;
    double t1, t2;
    emitNames();

    t1 = MPI_Wtime();
    waitUntillRdy();
    t2 = MPI_Wtime();
    bsp = t2 - t1;

    while (true) {

        splitToChunks(numChunks);

        t1 = MPI_Wtime();
        pending = 0;
        for (int i=1; i<worldSize; i++) {
            if (!sendNextChunk(i)) break;
            processSpeed[i][2] = MPI_Wtime();
            pending++;
        }

        int dest;
        while(pending>0) {
            switch(recvMessage()) {
                case EXIT: return; break;
                case PIXELS:
                    dest = recvPixels(status);
                    updateProcessSpeed();
                    if (!sendNextChunk(dest))
                        pending--;
                    break;
                default: break;
            }
           // emit workIsReady();
            emit processInfo(processSpeed);
        }
        t2 = MPI_Wtime();

        emit setTime(t2-t1);
        time += t2 - t1;

        //update camera pos
        camera->rotate();
        //broadcast camera
        sendCameraPointToPoint();

        emit workIsReady();

        if (n > 0) {
            n --;
            if (n == 0) break;
        }

    }
    printResult(time/test, bsp);
    emit close();
}
