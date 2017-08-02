#include "light.h"

Light::Light()
{
    pos = new float[3];
    pos[0] = 0.0;
    pos[0] = 0.0;
    pos[0] = 10.0;
    amb = new float[3];
    amb[0] = 0.1;
    amb[1] = 0.1;
    amb[2] = 0.1;
    dif = new float[3];
    dif[0] = 1.0;
    dif[1] = 1.0;
    dif[2] = 1.0;
    spec = new float[3];
    spec[0] = 1.0;
    spec[1] = 1.0;
    spec[2] = 1.0;
}

Light::Light(float *pos, float *amb, float *dif, float *spec)
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
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
}

void Light::setAmb(float r, float g, float b)
{
    amb[0] = r;
    amb[1] = g;
    amb[2] = b;
}

void Light::setDif(float r, float g, float b)
{
    dif[0] = r;
    dif[1] = g;
    dif[2] = b;
}

void Light::setSpec(float r, float g, float b)
{
    spec[0] = r;
    spec[1] = g;
    spec[2] = b;
}

float *Light::getSpec()
{
    return spec;
}

float *Light::getDif()
{
    return dif;
}

float *Light::getAmb()
{
    return amb;
}

float *Light::getPos()
{
    return pos;
}
