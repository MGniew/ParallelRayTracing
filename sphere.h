#ifndef SPHERE_H
#define SPHERE_H

#include "sceneobject.h"


class Sphere : public SceneObject
{
public:
    Sphere();
    ~Sphere();
    Vector3<float> getLocalColor(Vector3<float>& normalVector,
                                         Vector3<float>& crossPoint,
                                         Vector3<float>& observationVector); //returns RGB, uses Phong model
    bool trace(Vector3<float>& crossPoint,
               Vector3<float>& startPoint,
               Vector3<float>& directionVector); //returns true if hit, cordinates in param
    Vector3<float> getNormalVector(Vector3<float>& crossPoint);

    float radius;
};

#endif // SPHERE_H
