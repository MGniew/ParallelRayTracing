#ifndef PIXELS_H
#define PIXELS_H

#include "vector"
#include "vector3.h"

class Pixels
{
public:

    Pixels(int x, int y);
    ~Pixels();
    void serialize(std::vector<char> *bytes, int startx, int stopx, int starty, int stopy);
    void deserialize(const std::vector<char>& bytes);
    Vector3<float>*** data;
    int x, y;
    int serializedSize;


};

#endif // PIXELS_H
