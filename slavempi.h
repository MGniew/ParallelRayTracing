#ifndef SLAVE_H
#define SLAVE_H

#include "vector3.h"
#include "camera.h"
#include "scene.h"
#include "raytracer.h"
#include "mpi.h"
#include "vector"
#include "fileloader.h" //temp

class SlaveMPI
{
public:
    SlaveMPI();
    int exec();

    int x, y;
    Vector3<float>*** pixels;
    Camera* camera;
    Scene* scene;

};

#endif // SLAVE_H
