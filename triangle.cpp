#include "triangle.h"

Triangle::Triangle()
{

}

Triangle::~Triangle()
{

}

bool Triangle::trace(Vector3<float>* crossPoint, Vector3<float>* startPoint, Vector3<float>* directionVector) {
    return false;
}

Vector3<float>* Triangle::getNormalVector(Vector3<float>* crossPoint) {
    return nullptr;
}

Vector3<float>* Triangle::getPixelColor(Vector3<float>* normalVector) {
    return nullptr;
}
