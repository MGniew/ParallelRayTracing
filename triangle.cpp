#include "triangle.h"

Triangle::Triangle(Vector3<float> *pointA,
                   Vector3<float> *pointB,
                   Vector3<float> *pointC,
                   Vector3<float> *normalA,
                   Vector3<float> *normalB,
                   Vector3<float> *normalC,
                   float texCoordsX, float texCoordsY,
                   Vector3<float>* amb,
                   Vector3<float>* dif,
                   Vector3<float>* spec,
                   float specShin,
                   float transparency,
                   float mirror,
                   float local,
                   float density) : SceneObject(amb, dif, spec, specShin, transparency, mirror, local, density)
{


    Vector3<float> ab = *pointB - *pointA;
    Vector3<float> ac = *pointC - *pointA;
    Vector3<float> normal = ab.vectorProduct(ac).normalize();



    this->pointA = pointA;
    this->pointB = pointB;
    this->pointC = pointC;
    normalA->setValues(normal.x, normal.y, normal.z);
    normalB->setValues(normal.x, normal.y, normal.z);
    normalC->setValues(normal.x, normal.y, normal.z);
    this->normalA = normalA;
    this->normalB = normalB;
    this->normalC = normalC;
//    if (normalA != nullptr)
//        this->normalA = normalA;
//    else
//        normalA = new Vector3<float>(normal.x, normal.y, normal.z);

//    if (normalB != nullptr)
//        this->normalB = normalB;
//    else
//        this->normalB = new Vector3<float>(normal.x, normal.y, normal.z);

//    if (normalC != nullptr)
//        this->normalC = normalC;
//    else
//        this->normalC = new Vector3<float>(normal.x, normal.y, normal.z);

    std::cout << normalA->x << " " << normalA->y << " " << normalA->z << std::endl;
    this->texCoordsX = texCoordsX;
    this->texCoordsY = texCoordsY;

}

Triangle::Triangle() : SceneObject(new Vector3<float>(0.5, 0.5, 0.5), new Vector3<float>(0.3, 0.3, 0.1),
                                   new Vector3<float>(0.7, 0.7, 0.7), 39, 0.0, 0.0, 1.0, 0.0)
{
    pointA = new Vector3<float>(0.0, 2.0, 2.0);
    pointB = new Vector3<float>(-2.0, 0, 2.0);
    pointC = new Vector3<float>(2.0, 0, 2.0);

    Vector3<float> ab = *pointB - *pointA;
    Vector3<float> ac = *pointC - *pointA;
    Vector3<float> normal = ab.vectorProduct(ac).normalize();

    normalA = new Vector3<float>(normal.x, normal.y, normal.z);
    normalB = new Vector3<float>(normal.x, normal.y, normal.z);
    normalC = new Vector3<float>(normal.x, normal.y, normal.z);

}

Triangle::~Triangle()
{
    delete pointA;
    delete pointB;
    delete pointC;
    delete normalA;
    delete normalB;
    delete normalC;
}

bool Triangle::trace(Vector3<float>& crossPoint, Vector3<float>& startPoint, Vector3<float>& directionVector) {

    Vector3<float> ab = *pointB - *pointA;
    Vector3<float> ac = *pointC - *pointA;

    Vector3<float> normal = ab.vectorProduct(ac);
    normal.normalize();

    //step1: find crosspoint with plane
    float NdotRayDirection = normal.scalarProduct(directionVector);
    if (fabs(NdotRayDirection) < 0.000001) // almost 0 (also in sphere change that!)
        return false;
    float d = normal.scalarProduct(*pointA);
    float t = (d - normal.scalarProduct(startPoint))/NdotRayDirection;
    // check if the triangle is in behind the ray
    if (t < 0) return false; // the triangle is behind

    crossPoint = startPoint + directionVector*t;
    // Step 2: inside-outside test
    Vector3<float> C; // vector perpendicular to triangle's plane

    Vector3<float> edge0 = *pointB - *pointA;
    Vector3<float> vp0 = crossPoint - *pointA;
    C = edge0.vectorProduct(vp0);
    if (normal.scalarProduct(C) < 0) return false; // P is on the right side

    Vector3<float> edge1 = *pointC - *pointB;
    Vector3<float> vp1 = crossPoint - *pointB;
    C = edge1.vectorProduct(vp1);
    if (normal.scalarProduct(C) < 0) return false; // P is on the right side

    Vector3<float> edge2 = *pointA - *pointC;
    Vector3<float> vp2 = crossPoint - *pointC;
    C = edge2.vectorProduct(vp2);
    if (normal.scalarProduct(C) < 0) return false; // P is on the right side;

    return true;

}

Vector3<float> Triangle::getNormalVector(Vector3<float>& crossPoint) {

    //consider cache those
    Vector3<float> ab = *pointA - *pointB;
    Vector3<float> bc = *pointB - *pointC;
    Vector3<float> ca = *pointC - *pointA;

    Vector3<float> ap = *pointA - crossPoint;
    Vector3<float> bp = *pointB - crossPoint;

    float abArea = Area(ab, ap);
    float bcArea = Area(bc, bp);
    float caArea = Area(ca, ap);

    //this may be a const
    float area = abArea + bcArea + caArea;
    Vector3<float> result = (*normalA*bcArea + *normalB*caArea + *normalC*abArea);
    result = result/area;
    return result;
   // return Vector3<float>(normalA->x, normalB->y, normalC->z);
}

float Triangle::Area(Vector3<float> a, Vector3<float> b)
{
   return a.vectorProduct(b).length()/2;
}
