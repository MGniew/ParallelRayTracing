#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "vector3.h"
#include "camera.h"
#include "scene.h"
#include <list>
#include <iostream>

class SceneObject;

class RayTracer
{
public:
    RayTracer();

    void basicRaytracer();
    SceneObject* getClosest(Vector3<float>& crossPoint,
                            Vector3<float>& startPoint,
                            Vector3<float>& directionVector);

};

#endif // RAYTRACER_H
