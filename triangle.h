#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "sceneobject.h"

class Triangle : public SceneObject
{
public:
    Triangle();
    ~Triangle();
    Vector3<float>* getPixelColor(Vector3<float>* normalVector) = 0; //returns RGB, uses Phong model
    bool trace(Vector3<float>* crossPoint,
                       Vector3<float>* startPoint,
                       Vector3<float>* directionVector) = 0; //returns true if hit, cordinates in param
    Vector3<float>* getNormalVector(Vector3<float>* crossPoint) = 0;
};

#endif // TRIANGLE_H
