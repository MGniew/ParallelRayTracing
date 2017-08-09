#include "triangle.h"

Triangle::Triangle()
{

}

Triangle::~Triangle()
{

}

bool Triangle::trace(Vector3<float>& crossPoint, Vector3<float>& startPoint, Vector3<float>& directionVector) {
    return false;
}

Vector3<float> Triangle::getNormalVector(Vector3<float>& crossPoint) {
    return Vector3<float>();
}


Vector3<float> Triangle::getLocalColor(Vector3<float>& normalVector,
                                     Vector3<float>& crossPoint,
                                     Vector3<float>& observationVector) {
    return Vector3<float>();
}
