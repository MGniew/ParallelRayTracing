#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "vector3.h"
#include "scene.h"
#include <cstdlib>
#include <ctime>
#include "serializable.h"


class BSP;

class SceneObject : public Serializable
{
public:
    SceneObject();
    SceneObject(Vector3<float>* amb,
                Vector3<float>* dif,
                Vector3<float>* spec,
                float specShin,
                float transparency,
                float mirror,
                float local,
                float density);

    virtual ~SceneObject();
    Vector3<float> getLocalColor(Vector3<float>& normalVector,
                                 Vector3<float>& crossPoint,
                                 Vector3<float>& observationVector,
                                 BSP *bsp);

    bool isInShadow(Vector3<float>& crossPoint, Vector3<float>& directionVector, Vector3<float>& lightPos);

    virtual bool trace(Vector3<float> &crossPoint,
                       Vector3<float> &startPoint,
                       Vector3<float> &directionVector,
                       float &dist) = 0;
    virtual Vector3<float> getNormalVector(Vector3<float> &crossPoint) = 0;
    virtual void print() = 0;

    float getSpecShin();
    void setSpecShin(float value);

    Vector3<float>* getSpec();
    void setSpec(float r, float g, float b);

    Vector3<float>* getDif();
    void setDif(float r, float g, float b);

    Vector3<float>* getAmb();
    void setAmb(float r, float g, float b);

    float getTransparency();

    void setTransparency(float value);

    float getMirror();
    void setMirror(float value);

    float getLocal();
    void setLocal(float value);

    float getDensity();
    void setDensity(float value);

protected:
    Vector3<float>* amb;
    Vector3<float>* dif;
    Vector3<float>* spec;
    float specShin;

    //theoreticly trans + mir + local = 1, but lets make it more interesting
    float transparency;
    float mirror;
    float local;
    float density;



};

#endif // SCENEOBJECT_H
