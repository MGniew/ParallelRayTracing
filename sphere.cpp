#include "sphere.h"

Sphere::Sphere(Vector3<float>* amb,
               Vector3<float>* dif,
               Vector3<float>* spec,
               float specShin,
               Vector3<float>* pos,
               float radius,
               float transparency,
               float mirror,
               float local,
               float density) : SceneObject(amb, dif, spec, specShin, transparency, mirror, local, density)
{
    this->pos = pos;
    this->radius = radius;
}

Sphere::~Sphere()
{

}

bool Sphere::trace(Vector3<float>& crossPoint, Vector3<float>& startPoint, Vector3<float>& directionVector) {

     float a, b, c, d, r1, r2;
     float sqr;

     Vector3<float> distance = startPoint-*pos;
     a = directionVector.scalarProduct(directionVector);
     b = 2 * directionVector.scalarProduct(distance);
     c = distance.scalarProduct(distance) - radius*radius;

     d = b*b - 4*a*c;

     if (d<0) return false;
     sqr = sqrt(d);
         if (d>0) {
            r1 = (-b - sqr)/(2*a);
            r2 = (-b + sqr)/(2*a);
            if (r1 < 0 && r2 < 0) return false;
            if (r1 < 0)
                r1 = r2;
         } else
             r1 = (-b)/(2*a);

         crossPoint.x = startPoint.x + r1*directionVector.x;
         crossPoint.y = startPoint.y + r1*directionVector.y;
         crossPoint.z = startPoint.z + r1*directionVector.z;
         return true;

}

Vector3<float> Sphere::getNormalVector(Vector3<float>& crossPoint) {

    Vector3<float> normalVector = crossPoint - *pos;
    return normalVector.normalize();
}
