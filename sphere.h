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
    bool trace(Vector3<float>& crossPoint,
               Vector3<float>& startPoint,
               Vector3<float>& directionVector); //returns true if hit, cordinates in param
    Vector3<float> getNormalVector(Vector3<float>& crossPoint);

    float radius;
    Vector3<float>* pos;

    void serialize(std::vector<char> *bytes);
    void deserialize(const std::vector<char>& bytes);
    char getType();
};

#endif // SPHERE_H
