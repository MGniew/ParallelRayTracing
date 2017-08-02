#include "sceneobject.h"

SceneObject::SceneObject()
{

}

SceneObject::~SceneObject()
{

}

float SceneObject::getSpecShin() const
{
    return specShin;
}

void SceneObject::setSpecShin(float value)
{
    specShin = value;
}

float *SceneObject::getSpec() const
{
    return spec;
}

void SceneObject::setSpec(float *value)
{
    spec = value;
}

float *SceneObject::getDif() const
{
    return dif;
}

void SceneObject::setDif(float *value)
{
    dif = value;
}

float *SceneObject::getAmb() const
{
    return amb;
}

void SceneObject::setAmb(float *value)
{
    amb = value;
}
