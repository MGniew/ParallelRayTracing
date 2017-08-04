#include "sceneobject.h"

SceneObject::SceneObject()
{

}

SceneObject::~SceneObject()
{

}

float SceneObject::getSpecShin()
{
    return specShin;
}

void SceneObject::setSpecShin(float value)
{
    specShin = value;
}

Vector3<float>* SceneObject::getSpec()
{
    return spec;
}

void SceneObject::setSpec(float r, float g, float b)
{
    spec->x = r;
    spec->y = g;
    spec->z = b;
}

Vector3<float>* SceneObject::getDif()
{
    return dif;
}

void SceneObject::setDif(float r, float g, float b)
{
    dif->x = r;
    dif->y = g;
    dif->z = b;
}

Vector3<float>* SceneObject::getAmb()
{
    return amb;
}

void SceneObject::setAmb(float r, float g, float b)
{
    amb->x = r;
    amb->y = g;
    amb->z = b;
}
