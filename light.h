#ifndef LIGHT_H
#define LIGHT_H

#include "vector3.h"

class Light
{
public:
    Light();
    Light(Vector3<float>* pos, Vector3<float>* amb, Vector3<float>* dif, Vector3<float>* spec);
    ~Light();

    Vector3<float>* pos;
    Vector3<float>* amb;
    Vector3<float>* dif;
    Vector3<float>* spec;

    Vector3<float>* getPos();
    Vector3<float>* getAmb();
    Vector3<float>* getDif();
    Vector3<float>* getSpec();
    void setPos(float x, float y, float z);
    void setAmb(float r, float g, float b);
    void setDif(float r, float g, float b);
    void setSpec(float r, float g, float b);
    int serializedSize;
    void serialize(std::vector<char> *bytes);
    void deserialize(const std::vector<char>& bytes);

};

#endif // LIGHT_H
