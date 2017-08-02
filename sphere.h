#ifndef SPHERE_H
#define SPHERE_H

#include "sceneobject.h"

class Sphere : public SceneObject
{
public:
    Sphere();
    ~Sphere();
    float* getPixelColor(float* normalVector) = 0; //returns RGB, uses Phong model
    bool trace(float* crossPoint,
                       float* startPoint,
                       float* directionVector) = 0; //returns true if hit, cordinates in param
    float* getNormalVector(float* crossPoint) = 0;
};

#endif // SPHERE_H
