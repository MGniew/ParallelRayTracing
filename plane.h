#ifndef PLANE_H
#define PLANE_H

#include "sceneobject.h"
#include "triangle.h"
#include "sphere.h"
#include "global.h"
#include "vector3.h"

class Plane
{
public:
    Plane();
    Plane(float a, float b, float c, float d);

    float a;
    float b;
    float c;
    float d;

    int classifyObject(SceneObject* obj);
    int classifyPoint(Vector3<float>* point);
    float getDistToPoint(Vector3<float>* point);
    bool rayIntersectPlane(Vector3<float> startingPoint, Vector3<float> directionVector);
    Vector3<float> getNormal();
    bool isValid();
    void print();

};

#endif // PLANE_H
