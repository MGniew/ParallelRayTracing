#ifndef SPHERE_H
#define SPHERE_H

#include "sceneobject.h"
#include "global.h"
#include "boundingbox.h"

using namespace myGlobals;

class BoundingBox;

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
    Sphere();
    bool trace(Vector3<float>& crossPoint,
               Vector3<float>& startPoint,
               Vector3<float>& directionVector,
               float &dist);
    Vector3<float> getNormalVector(Vector3<float>& crossPoint);
    void print();
    BoundingBox getBoundingBox();
    float getRadius();
    Vector3<float>* getPos();

    void serialize(std::vector<char> *bytes);
    void deserialize(const std::vector<char>& bytes);
    char getType();


private:
    float radius;
    Vector3<float>* pos;

};

#endif // SPHERE_H
