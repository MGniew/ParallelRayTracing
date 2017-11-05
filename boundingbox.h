#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include <algorithm>
#include "vector3.h"

class BoundingBox {

public:
    BoundingBox();
    bool intersect(Vector3<float> startingPoint, Vector3<float> direction);

    float minX;
    float maxX;
    float minY;
    float maxY;
    float minZ;
    float maxZ;
};

#endif // BOUNDINGBOX_H


