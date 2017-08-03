#include "sphere.h"

Sphere::Sphere()
{

}

Sphere::~Sphere()
{

}

bool Sphere::trace(Vector3<float>& crossPoint, Vector3<float>& startPoint, Vector3<float>& directionVector) {

     float a, b, c, d, r;

     a = directionVector.scalarProduct(directionVector);
     b = 2 * startPoint.scalarProduct(directionVector);
     c = startPoint.scalarProduct(startPoint) - radius;

     d = b*b - 4*a*c;

     if (d>=0) {
        r = -b - sqrt(d/(2*a));

        crossPoint.x = startPoint.x + r*directionVector.x;
        crossPoint.y = startPoint.y + r*directionVector.y;
        crossPoint.z = startPoint.z + r*directionVector.z;

        return true;
     }
     return false;
}

Vector3<float> Sphere::getNormalVector(Vector3<float>& crossPoint) {

    return Vector3<float>(crossPoint.x, crossPoint.y, crossPoint.z);
}
//WIP
Vector3<float> Sphere::getPixelColor(Vector3<float>& normalVector, Vector3<float>& crossPoint) {

    //for now make it work for 1 light source.
    Vector3<float>* lightPossition = Scene::getInstance()->Lights[0]->pos;
    Vector3<float> lightVector = *lightPossition - crossPoint;
    lightVector.normalize();
    float n_dot_l = lightVector.scalarProduct(normalVector);
    Vector3<float> reflectionVector = normalVector*(2*n_dot_l) - lightVector;
    reflectionVector.normalize();
    //float v_dot_r = reflectionVector.scalarProduct() // kierunkiem obserwacji
}
