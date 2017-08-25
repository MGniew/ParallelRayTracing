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
}

void MasterThread::run()
{


    RayTracer rayTracer;
    rayTracer.recursiveRayTracer(2);
    emit workIsReady();

//    while(isAlive)
//    {

//    }
}
