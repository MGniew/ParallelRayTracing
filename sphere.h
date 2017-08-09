#ifndef SPHERE_H
#define SPHERE_H

#include "sceneobject.h"


class Sphere : public SceneObject
{
public:
    Sphere(Vector3<float>* amb,
           Vector3<float>* dif,
           Vector3<float>* spec,
           float specShin,
           Vector3<float>* pos,
           float radius,
           float transparency,
           float mirror,
           float local,
           float density);
    ~Sphere();
    Vector3<float> getLocalColor(Vector3<float>& normalVector,
                                         Vector3<float>& crossPoint,
                                         Vector3<float>& observationVector); //returns RGB, uses Phong model
    bool trace(Vector3<float>& crossPoint,
               Vector3<float>& startPoint,
               Vector3<float>& directionVector); //returns true if hit, cordinates in param
    Vector3<float> getNormalVector(Vector3<float>& crossPoint);
    bool isInShadow(Vector3<float>& crossPoint, Vector3<float>& directionVector, Vector3<float>& lightPos);

    float radius;
    Vector3<float>* pos;
};

#endif // SPHERE_H
