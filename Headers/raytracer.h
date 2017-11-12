#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "vector3.h"
#include "camera.h"
#include <list>
#include <iostream>
#include "global.h"

using namespace myGlobals;

class SceneObject;
class Scene;

class RayTracer
{
public:
    RayTracer();
    ~RayTracer();

    void basicRayTracer();
    void recursiveRayTracer(int depth);
    Vector3<float> getColorRecursive(Vector3<float> startPoint,
                                     Vector3<float> directionVector,
                                     int depth);

    Scene* scene;
    Camera* camera;

};

#endif // RAYTRACER_H
