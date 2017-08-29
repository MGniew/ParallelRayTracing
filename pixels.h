#ifndef PIXELS_H
#define PIXELS_H

#include "vector"
#include "vector3.h"
#include "iostream"

class Pixels
{
public:

    Pixels(int x, int y);
    ~Pixels();
    void serialize(std::vector<char> *bytes, int startx, int stopx, int starty, int stopy);
    void deserialize(const std::vector<char>& bytes);
    Vector3<float>*** data;
    int x, y;
    int startx, starty;
    int serializedSize;
    void setStartXY(int x, int y);


};

#endif // PIXELS_H
