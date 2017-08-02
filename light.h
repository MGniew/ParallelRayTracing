#ifndef LIGHT_H
#define LIGHT_H


class Light
{
public:
    Light();
    Light(float* pos, float* amb, float* dif, float* spec);
    ~Light();

    float* pos;
    float* amb;
    float* dif;
    float* spec;

    float *getPos();
    float *getAmb();
    float *getDif();
    float *getSpec();
    void setPos(float x, float y, float z);
    void setAmb(float r, float g, float b);
    void setDif(float r, float g, float b);
    void setSpec(float r, float g, float b);

};

#endif // LIGHT_H
