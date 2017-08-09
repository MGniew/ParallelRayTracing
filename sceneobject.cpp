#include "sceneobject.h"

SceneObject::SceneObject()
{

}


SceneObject::SceneObject(Vector3<float>* amb,
                         Vector3<float>* dif,
                         Vector3<float>* spec,
                         float specShin,
                         float transparency,
                         float mirror,
                         float local,
                         float density){
    this->amb = amb;
    this->dif = dif;
    this->spec = spec;
    this->specShin = specShin;
    this->transparency= transparency;
    this->mirror = mirror;
    this->local = local;
    if (density < 1)
        density = 1;
    this->density = density;

}

SceneObject::~SceneObject()
{
    delete spec;
    delete dif;
    delete amb;
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

float SceneObject::getTransparency()
{
    return transparency;
}

void SceneObject::setTransparency(float value)
{
    transparency = value;
}

float SceneObject::getMirror()
{
    return mirror;
}

void SceneObject::setMirror(float value)
{
    mirror = value;
}

float SceneObject::getLocal()
{
    return local;
}

void SceneObject::setLocal(float value)
{
    local = value;
}

float SceneObject::getDensity()
{
    return density;
}

void SceneObject::setDensity(float value)
{
    density = value;
}
