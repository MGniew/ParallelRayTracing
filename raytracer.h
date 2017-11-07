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

    SceneObject* getClosest(Vector3<float>& crossPoint,
                            Vector3<float>& startPoint,
                            Vector3<float>& directionVector);

    Scene* scene;
    Camera* camera;

    Vector3<float>*** buffer;

};

#endif // RAYTRACER_H
