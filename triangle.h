#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "sceneobject.h"
#include "global.h"
#include "list"


class BoundingBox;
class Plane;

using namespace myGlobals;

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
            float texCoordsY,
             Vector3<float> *amb,
             Vector3<float> *dif,
             Vector3<float> *spec,
             float specShin,
             float transparency,
             float mirror,
             float local,
             float density);

    ~Triangle();
    Triangle();
    Triangle(Triangle &triangle);

    bool trace(Vector3<float>& crossPoint,
                       Vector3<float>& startPoint,
                       Vector3<float>& directionVector,
                       float& dist);
    Vector3<float> getNormalVector(Vector3<float>& crossPoint);
    void print();
    BoundingBox getBoundingBox();


    static float Area(Vector3<float> a, Vector3<float> b);


    Vector3<float> *pointA;
    Vector3<float> *pointB;
    Vector3<float> *pointC;
    Vector3<float> *normalA;
    Vector3<float> *normalB;
    Vector3<float> *normalC;
    Plane getPlane();
    Plane getPerpendicularPlane(int i);
    std::list<Plane> getPlanes();
    Vector3<float>* getPointbyNum(int a);
    void split(Plane plane, std::list<Triangle*> & front, std::list<Triangle*> & back);

    float texCoordsX;
    float texCoordsY;

    void serialize(std::vector<char> *bytes);
    void deserialize(const std::vector<char>& bytes);
    char getType();

};

#endif // TRIANGLE_H
