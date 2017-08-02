#ifndef LIGHT_H
#define LIGHT_H


class Light
{
public:
    Light();
    ~Light();

    float* pos;
    float* amb;
    float* dif;
    float* spec;
};

#endif // LIGHT_H
