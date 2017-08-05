#include "light.h"

Light::Light()
{
    pos = new Vector3<float>(.0, 3.0, -10.0);
    amb = new Vector3<float>(0.0, 0.0, 0.0);
    dif = new Vector3<float>(0.0, 1.0, 1.0);
    spec = new Vector3<float>(1.0, 1.0, 0.0);
}

Light::Light(Vector3<float>* pos, Vector3<float>* amb, Vector3<float>* dif, Vector3<float>* spec)
{
    this->pos = pos;
    this->amb = amb;
    this->dif = dif;
    this->spec = spec;
}

Light::~Light()
{
    delete pos;
    delete amb;
    delete dif;
    delete spec;
}

void Light::setPos(float x, float y, float z)
{
    pos->x = x;
    pos->y = y;
    pos->z = z;
}

void Light::setAmb(float r, float g, float b)
{
    amb->x = r;
    amb->y = g;
    amb->z = b;
}

void Light::setDif(float r, float g, float b)
{
    dif->x = r;
    dif->y = g;
    dif->z = b;
}

void Light::setSpec(float r, float g, float b)
{
    spec->x = r;
    spec->y = g;
    spec->z = b;
}

Vector3<float>* Light::getSpec()
{
    return spec;
}

Vector3<float>* Light::getDif()
{
    return dif;
}

Vector3<float>* Light::getAmb()
{
    return amb;
}

Vector3<float>* Light::getPos()
{
    return pos;
}
