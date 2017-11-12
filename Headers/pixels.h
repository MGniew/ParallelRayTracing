#ifndef PIXELS_H
#define PIXELS_H

#include "vector"
#include "vector3.h"
#include "iostream"
#include "serializable.h"

class Pixels : public Serializable
{
public:

    Pixels(int x, int y);
    ~Pixels();
    void serialize(std::vector<char> *bytes);
    void deserialize(const std::vector<char>& bytes);
    char getType();
    unsigned char* data;
    int x, y;
    int startx, starty;
    void setStartXY(int x, int y);
    void setPixel(int posX, int posY, Vector3<float>& vec);

};

#endif // PIXELS_H
