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
    numChunks=chunks;
    this->depth = depth;
    this->test = test;

}


MasterThread::~MasterThread()
{
    isAlive = false;
    wait();
    delete scene;

}



void MasterThread::run()
{
    double time = 0; double bsp = 0;
    int n = test;
    clock_t t1, t2;
    RayTracer rayTracer;

    if (bsp) {
        scene->buildBSP(1000);
    }

    while (true) {

        t1 =clock();
        rayTracer.recursiveRayTracer(depth);
        t2 = clock();
        time = double(t2 - t1)/ CLOCKS_PER_SEC;
        emit setTime(time);

        //update camera pos
        camera->rotate();

        emit workIsReady();

        if (n > 0) {
            n --;
            if (n == 0) break;
        }

    }

    emit close();
}
