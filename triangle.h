#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "sceneobject.h"

class Triangle : public SceneObject
{
public:
    Triangle();
    ~Triangle();
    float* getPixelColor(float* normalVector) = 0; //returns RGB, uses Phong model
    bool trace(float* crossPoint,
                       float* startPoint,
                       float* directionVector) = 0; //returns true if hit, cordinates in param
    float* getNormalVector(float* crossPoint) = 0;
};

#endif // TRIANGLE_H
