#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "vector3.h"

class SceneObject
{
public:
    SceneObject();
    ~SceneObject();
    virtual Vector3<float>* getPixelColor(Vector3<float>* normalVector) = 0; //returns RGB, uses Phong model
    virtual bool trace(Vector3<float>* crossPoint,
                       Vector3<float>* startPoint,
                       Vector3<float>* directionVector) = 0; //returns true if hit, cordinates in param
    virtual Vector3<float>* getNormalVector(Vector3<float>* crossPoint) = 0;

    float getSpecShin();
    void setSpecShin(float value);

    float *getSpec();
    void setSpec(float *value);

    float *getDif();
    void setDif(float *value);

    float *getAmb();
    void setAmb(float *value);

private:
    float* amb;
    float* dif;
    float* spec;
    float specShin;
};

#endif // SCENEOBJECT_H
