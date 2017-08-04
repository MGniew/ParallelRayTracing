#include "sphere.h"

Sphere::Sphere(Vector3<float>* amb,
               Vector3<float>* dif,
               Vector3<float>* spec,
               float specShin,
               Vector3<float>* pos,
               float radius) : SceneObject(amb, dif, spec, specShin)
{
    this->pos = pos;
    this->radius = radius;
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

//WIP /crosspoint, normalVector, observationVector (ray to object!)

//possible bugs:
    // - observationVector shlould be normalized and multpily by *-1
    // normal vector should be normalized
    // pow??
    // return statment
    // TODO::multpile light source
    // why not now? because Im going forward to implement early beta raytracer

Vector3<float> Sphere::getLocalColor(Vector3<float>& normalVector,
                                     Vector3<float>& crossPoint,
                                     Vector3<float>& observationVector) {

    Scene* scene = Scene::getInstance();
    //for now make it work for 1 light source.
    Vector3<float>* lightPossition = scene->Lights[0]->pos;
    Vector3<float> lightVector = *lightPossition - crossPoint;
    lightVector.normalize();
    float n_dot_l = lightVector.scalarProduct(normalVector);
    Vector3<float> reflectionVector = normalVector*(2*n_dot_l) - lightVector;
    reflectionVector.normalize();
    float v_dot_r = reflectionVector.scalarProduct(observationVector);
    if (v_dot_r < 0)
        v_dot_r = 0;

    if (n_dot_l > 0)
        return  (dif->multiplyByVector(*scene->Lights[0]->dif))*n_dot_l +
                spec->multiplyByVector(*scene->Lights[0]->spec)*pow(double(v_dot_r), 20.0) +
                amb->multiplyByVector(*scene->Lights[0]->amb) +
                amb->multiplyByVector(*scene->getGlobalAmbient());
    else
        return amb->multiplyByVector(*scene->getGlobalAmbient());

}

