#ifndef SLAVE_H
#define SLAVE_H

#include "vector3.h"
#include "camera.h"
#include "scene.h"
#include "raytracer.h"
#include "mpi.h"
#include "vector"
#include "pixels.h"
#include "global.h"

using namespace myGlobals;

class SlaveMPI
{
public:
    SlaveMPI();
    ~SlaveMPI();
    int exec();

    int x, y;
    int depth;
    Vector3<float>*** pixels;
    Camera* camera;
    Scene* scene;
    MPI_Status status;
    void recvCamera();
    void recvScene();
    void recvDepth();
    void recvChunk();
    int recvMessage();
    void sendPixels();

};

#endif // SLAVE_H
