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

    Vector3<float> ab = pointB - pointA;
    Vector3<float> ac = pointC - pointA;

    Vector3<float> normal = ab.vectorProduct(ac);
    float area = normal.length();

    //step1: find crosspoint with plane

     // check if ray and plane are parallel ?
    float NdotRayDirection = normal.scalarProduct(directionVector);
    if (fabs(NdotRayDirection) < 0.0001) // almost 0 (also in sphere chenge that!)
        return false;


    // compute d parameter using equation 2
    float d = normal.scalarProduct(pointA);

    // compute t (equation 3)
    float t = (normal.scalarProduct(startPoint) + d)/NdotRayDirection;
    // check if the triangle is in behind the ray
    if (t < 0) return false; // the triangle is behind

    // compute the intersection point using equation 1
    crossPoint = startPoint + directionVector*t;

    // Step 2: inside-outside test
    Vector3<float> C; // vector perpendicular to triangle's plane

    // edge 0
    Vector3<float> edge0 = pointB - pointA;
    Vector3<float> vp0 = crossPoint - pointA;
    C = edge0.vectorProduct(vp0);
    if (normal.scalarProduct(C) < 0) return false; // P is on the right side

    // edge 1
    Vector3<float> edge1 = pointC - pointB;
    Vector3<float> vp1 = crossPoint - pointB;
    C = edge1.vectorProduct(vp1);
    if (normal.scalarProduct(C) < 0) return false; // P is on the right side

    // edge 2
    Vector3<float> edge2 = pointA - pointC;
    Vector3<float> vp2 = crossPoint - pointC;
    C = edge2.vectorProduct(vp2);
    if (normal.scalarProduct(C) < 0) return false; // P is on the right side;

    return true; // this ray hits the triangle

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
