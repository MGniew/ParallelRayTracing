#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "vector3.h"
#include "scene.h"
#include <cstdlib>
#include <ctime>

class SceneObject
{
public:
    SceneObject();
    SceneObject(Vector3<float>* amb, Vector3<float>* dif, Vector3<float>* spec, float specShin);
    virtual ~SceneObject();
    virtual Vector3<float> getLocalColor(Vector3<float>& normalVector,
                                                 Vector3<float>& crossPoint,
                                                 Vector3<float>& observationVector) = 0; //returns RGB, uses Phong model
    virtual bool trace(Vector3<float> &crossPoint,
                       Vector3<float> &startPoint,
                       Vector3<float> &directionVector) = 0; //returns true if hit, cordinates in param
    virtual Vector3<float> getNormalVector(Vector3<float> &crossPoint) = 0;

    float getSpecShin();
    void setSpecShin(float value);

    Vector3<float>* getSpec();
    void setSpec(float r, float g, float b);

    Vector3<float>* getDif();
    void setDif(float r, float g, float b);

    Vector3<float>* getAmb();
    void setAmb(float r, float g, float b);

protected:
    Vector3<float>* amb;
    Vector3<float>* dif;
    Vector3<float>* spec;
    float specShin;
};

#endif // SCENEOBJECT_H
