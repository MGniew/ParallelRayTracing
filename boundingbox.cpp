#include "boundingbox.h"

BoundingBox::BoundingBox()
{

}

bool BoundingBox::intersect(Vector3<float> startingPoint, Vector3<float> direction)
{

    Vector3<float> invDir(1/direction.x, 1/direction.y, 1/direction.z);

    float tmin = (minX - startingPoint.x) * invDir.x;
    float tmax = (maxX - startingPoint.x) * invDir.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (minY - startingPoint.y) * invDir.y;
    float tymax = (maxY - startingPoint.y) * invDir.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
    tmin = tymin;

    if (tymax < tmax)
    tmax = tymax;

    float tzmin = (minZ - startingPoint.z) * invDir.z;
    float tzmax = (maxZ - startingPoint.z) * invDir.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    if (tmax < 0)
        return false;

    return true;

}
