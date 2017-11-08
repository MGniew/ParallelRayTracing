#include "pixels.h"


Pixels::Pixels(int x, int y)
{
    this->x = x;
    this->y = y;
    startx = 0;
    starty = 0;
    serializedSize = sizeof(unsigned char)*x*y*3;
    data = new unsigned char[x*y*3];
}

Pixels::~Pixels()
{
    delete [] data;
    data = nullptr;
}

void Pixels::serialize(std::vector<char> *bytes)
{
    int stopx = startx + x;
    int stopy = starty + y;
    bytes->resize(serializedSize + 4*sizeof(int));
    char* ptr = bytes->data();
    memcpy(ptr, &startx, sizeof(int)); ptr += sizeof(int);
    memcpy(ptr, &stopx, sizeof(int)); ptr += sizeof(int);
    memcpy(ptr, &starty, sizeof(int)); ptr += sizeof(int);
    memcpy(ptr, &stopy, sizeof(int)); ptr += sizeof(int);
    memcpy(ptr, data, serializedSize);
}

void Pixels::deserialize(const std::vector<char> &bytes)
{
    const char* ptr = bytes.data();
    int startx, stopx, starty, stopy;
    memcpy(&startx, ptr, sizeof(int)); ptr += sizeof(int);
    memcpy(&stopx, ptr, sizeof(int)); ptr += sizeof(int);
    memcpy(&starty, ptr, sizeof(int)); ptr += sizeof(int);
    memcpy(&stopy, ptr, sizeof(int)); ptr += sizeof(int);

    for(int j=starty; j<stopy; j++) {
        memcpy(data + j*x*3 + startx*3, ptr, (stopx - startx)*3); ptr += (stopx - startx)*3;
    }
}

char Pixels::getType()
{
    return 'p';
}

void Pixels::setStartXY(int x, int y)
{
    this->startx = x;
    this->starty = y;
}

void Pixels::setPixel(int posX, int posY, Vector3<float> &vec)
{
    if(vec.x > 1) vec.x = 1;
    if(vec.y > 1) vec.y = 1;
    if(vec.z > 1) vec.z = 1;
    data[3*posY*x + 3*posX] = (int)(vec.x * 255);
    data[3*posY*x + 3*posX + 1] = (int)(vec.y * 255);
    data[3*posY*x + 3*posX + 2] = (int)(vec.z * 255);
}
