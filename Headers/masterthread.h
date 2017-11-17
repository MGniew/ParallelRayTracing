#ifndef MASTERTHREAD_H
#define MASTERTHREAD_H

#include "qthread.h"
#include "scene.h"
#include "camera.h"
#include "raytracer.h"
#include "fileloader.h"
#include "qwaitcondition.h"
#include <stdio.h>
#include "global.h"
#include "queue"
#include "vector"
#include "thread"
#include "chrono"
#include <string>
#include "qstring.h"
#include <ctime>

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
    int depth;

private:


    int numChunks;
    int test;


};

#endif // MASTERTHREAD_H
