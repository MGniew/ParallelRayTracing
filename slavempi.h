#ifndef SLAVE_H
#define SLAVE_H

#include "vector3.h"
#include "camera.h"
#include "scene.h"
#include "raytracer.h"
#include "mpi.h"
#include "vector"
#include "pixels.h"
#include "fileloader.h" //temp
#include "global.h"

class SlaveMPI
{
public:
    SlaveMPI();
    ~SlaveMPI();
    int exec();

    int x, y;
    Vector3<float>*** pixels;
    Camera* camera;
    Scene* scene;
    MPI_Status status;

};

#endif // SLAVE_H
