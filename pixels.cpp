#include "pixels.h"


Pixels::Pixels(int x, int y)
{

    this->x = x;
    this->y = y;
    startx = 0;
    starty = 0;
    serializedSize = Vector3<float>::serializedSize*x*y;

    data = new Vector3<float>**[x];
        for (int i = 0; i < x; i++) {
            data[i] = new Vector3<float>*[y];
            for (int j = 0; j < y; j++)
                data[i][j] = new Vector3<float>();
        }

}

Pixels::~Pixels()
{
    for (int i = 0; i <  x; i++) {
        for (int j = 0; j <  y; j++)
            delete data[i][j];
        delete [] data[i];
    }
    delete [] data;
    data = nullptr;
}

void Pixels::serialize(std::vector<char> *bytes, int startx, int stopx, int starty, int stopy)
{
    bytes->resize(serializedSize + 4*sizeof(int));
    char* ptr = bytes->data();
    std::vector<char> pixdataVec;
    memcpy(ptr, &startx, sizeof(int)); ptr += sizeof(int);
    memcpy(ptr, &stopx, sizeof(int)); ptr += sizeof(int);
    memcpy(ptr, &starty, sizeof(int)); ptr += sizeof(int);
    memcpy(ptr, &stopy, sizeof(int)); ptr += sizeof(int);

    for(int i=0; i<x; i++) {
        for(int j=0; j<y; j++) {
            data[i][j]->serialize(&pixdataVec);
            memcpy(ptr, pixdataVec.data(), pixdataVec.size());
            ptr += pixdataVec.size();
        }
    }
}

void Pixels::deserialize(const std::vector<char> &bytes)
{
    const char* ptr = bytes.data();
    int startx, stopx, starty, stopy;
    memcpy(&startx, ptr, sizeof(int)); ptr += sizeof(int);
    memcpy(&stopx, ptr, sizeof(int)); ptr += sizeof(int);
    memcpy(&starty, ptr, sizeof(int)); ptr += sizeof(int);
    memcpy(&stopy, ptr, sizeof(int)); ptr += sizeof(int);

    std::vector<char> pixdataVec;
    Vector3<float> pixVec;
    pixdataVec.resize(Vector3<float>::serializedSize);

    for(int i=startx; i<stopx; i++) {
        for(int j=starty; j<stopy; j++) {
            memcpy(pixdataVec.data(), ptr, pixdataVec.size());
            pixVec.deserialize(pixdataVec);
            data[i][j]->setValues(pixVec.x, pixVec.y, pixVec.z);
            ptr += pixdataVec.size();
        }
    }
}

void Pixels::setStartXY(int x, int y)
{
    this->startx = x;
    this->starty = y;
}
