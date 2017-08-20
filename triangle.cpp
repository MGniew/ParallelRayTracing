#include "triangle.h"

Triangle::Triangle(Vector3<float> *pointA,
                   Vector3<float> *pointB,
                   Vector3<float> *pointC,
                   Vector3<float> *normalA,
                   Vector3<float> *normalB,
                   Vector3<float> *normalC,
                   float texCoordsX, float texCoordsY)
{

}

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

    Vector3<float> ab = pointA - pointB;
    Vector3<float> bc = pointB - pointC;
    Vector3<float> ca = pointC - pointA;

    Vector3<float> ap = pointA - crossPoint;
    Vector3<float> bp = pointB - crossPoint;

    float abArea = Area(ab, ap);
    float bcArea = Area(bc, bp);
    float caArea = Area(ca, ap);

    //this may be a const
    float area = abArea + bcArea + caArea;

    return ((normalA*bcArea + normalB*caArea + normalC*abArea)/area).normalize();
}

float Triangle::Area(Vector3<float> a, Vector3<float> b)
{
   return a.vectorProduct(b).length()/2;
}


Vector3<float> Triangle::getLocalColor(Vector3<float>& normalVector,
                                     Vector3<float>& crossPoint,
                                     Vector3<float>& observationVector) {
    return Vector3<float>();
}
