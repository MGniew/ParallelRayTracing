#ifndef MASTERTHREAD_H
#define MASTERTHREAD_H

#include "qthread.h"
#include "scene.h"
#include "camera.h"
#include "raytracer.h"
#include "fileloader.h"
#include "qwaitcondition.h"


#include <mpi.h>
#include <stdio.h>

#include "global.h"
#include "queue"
#include "vector"
#include "thread"
#include "chrono"
#include <string>
#include "qstring.h"


using namespace myGlobals;



class MasterThread : public QThread
{
    Q_OBJECT

public:
    MasterThread(std::string file, int width, int height, int chunks, int depth, bool bsp, bool shadows, int test, QObject *parent = 0);
    ~MasterThread();
    int getNumOfChunks();

signals:
    void workIsReady();
    void setTime(double time);
    void processInfo(double **speeds);
    void close();
    void setName(int num, QString name);

protected:
    void run() override;

    bool isAlive;
    QWaitCondition condition;
    Camera* camera;
    Scene* scene;

    double** processSpeed;

private:
    void splitToChunks(int num);
    std::queue<Chunk> queue;
    int worldSize;
    MPI_Status status;
    void clearQueue(std::queue<Chunk> &q);
    void sendCameraBcast();
    void sendCameraPointToPoint();
    void sendScene();
    void sendDepth(int depth);
    bool sendNextChunk(int dest);
    void sendExitSignal();
    int recvPixels(MPI_Status &stat);
    int recvMessage();
    void finishPending();
    void updateProcessSpeed();
    void waitUntillRdy();
    void printResult(double spf, double bsp);
    void getNames();
    void emitNames();
    std::vector<std::string> names;
    int pending;
    int numChunks;
    int test;


};

#endif // MASTERTHREAD_H
