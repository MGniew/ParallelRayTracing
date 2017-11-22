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

private:
    int x, y;
    int depth;
    Vector3<float>*** pixels;
    Camera* camera;
    Scene* scene;
    MPI_Status status;
    void recvCameraBcast();
    void recvCameraPointToPoint();
    void recvScene();
    void recvDepth();
    void recvChunk();
    int recvMessage();
    void sendPixels();
    void sendName();
    void sendRdy();

};

#endif // SLAVE_H
