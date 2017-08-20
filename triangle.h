#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "sceneobject.h"

class Triangle : public SceneObject
{
public:
    Triangle(Vector3<float>* pointA,
            Vector3<float>* pointB,
            Vector3<float>* pointC,
            Vector3<float>* normalA,
            Vector3<float>* normalB,
            Vector3<float>* normalC,
            float texCoordsX,
            float texCoordsY);


    Triangle();
    ~Triangle();
    Vector3<float> getLocalColor(Vector3<float>& normalVector,
                                         Vector3<float>& crossPoint,
                                         Vector3<float>& observationVector); //returns RGB, uses Phong model
    bool trace(Vector3<float>& crossPoint,
                       Vector3<float>& startPoint,
                       Vector3<float>& directionVector); //returns true if hit, cordinates in param
    Vector3<float> getNormalVector(Vector3<float>& crossPoint);


    static float Area(Vector3<float> a, Vector3<float> b);


    Vector3<float> pointA;
    Vector3<float> pointB;
    Vector3<float> pointC;
    Vector3<float> normalA;
    Vector3<float> normalB;
    Vector3<float> normalC;
    float texCoordsX;
    float texCoordsY;

};

#endif // TRIANGLE_H
