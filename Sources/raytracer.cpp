#include "raytracer.h"
#include "sceneobject.h"
#include "scene.h"

RayTracer::RayTracer()
{
    scene = Scene::getInstance();
    camera = Camera::getInstance();
}

RayTracer::~RayTracer()
{
}

void RayTracer::recursiveRayTracer(int depth)
{

    Vector3<float> worldPosOfPixel;
    Vector3<float> directionVector;

    for(int i = 0; i < scene->getWidth(); i++) {
        for(int j = 0; j < scene->getHeight(); j++) {
            worldPosOfPixel = camera->getWorldPosOfPixel(i + scene->getStartX(),j + scene->getStartY());
            directionVector = worldPosOfPixel - *camera->getEye();
            directionVector.normalize();
            scene->setPixelColor(i, j, getColorRecursive(worldPosOfPixel, directionVector, depth));
        }
    }
}

Vector3<float> RayTracer::getColorRecursive(Vector3<float> startPoint,
                                            Vector3<float> directionVector,
                                            int depth)
{
    SceneObject* sceneObject;
    Vector3<float> crossPoint;
    Vector3<float> reflectedRay;
    Vector3<float> localColor;
    Vector3<float> reflectedColor;

    //refraction
    Vector3<float> transparencyColor;
    Vector3<float> transparencyRay;

    if (depth == 0)
        return Vector3<float>();

    depth--;

    sceneObject = scene->getClosest(crossPoint, startPoint, directionVector);

    if (sceneObject == nullptr)
        return Vector3<float>(*scene->getBackgroundColor());

     Vector3<float> normalVector = sceneObject->getNormalVector(crossPoint);
     Vector3<float> observationVector = directionVector*-1;


     if (observationVector.scalarProduct(normalVector) < 0) {
         normalVector = normalVector*-1;
     }

     crossPoint = crossPoint + normalVector*EPSILON;
     if(sceneObject->getTransparency()>0) {
         transparencyRay = directionVector.refract(normalVector, sceneObject->getDensity(), 1);
         transparencyColor = getColorRecursive(crossPoint, transparencyRay, depth);
     }

     if (sceneObject->getLocal()>0) {
         localColor.setValues(sceneObject->getLocalColor
                               (normalVector,
                               crossPoint,
                               observationVector));
     }
     if (sceneObject->getMirror()>0) {
         reflectedRay = directionVector.reflect(normalVector);
         reflectedColor = getColorRecursive(crossPoint, reflectedRay, depth);
     }

     return localColor*sceneObject->getLocal() + reflectedColor*sceneObject->getMirror() + transparencyColor*sceneObject->getTransparency();


}

void RayTracer::basicRayTracer()
{
    Vector3<float> worldPosOfPixel;
    Vector3<float> directionVector;
    Vector3<float> crossPoint;
    SceneObject* sceneObject;

    //for every pixel
    for(int i = 0; i < camera->getPixWidth(); i++) {
        for(int j = 0; j < camera->getPixHeight(); j++) {

            //get ray
            worldPosOfPixel = camera->getWorldPosOfPixel(i,j);

            //calcualte starting dir vector
            directionVector = worldPosOfPixel - *camera->getEye();
            directionVector.normalize();

            sceneObject = scene->getClosest(crossPoint, worldPosOfPixel, directionVector);


            if (sceneObject == nullptr) {
                scene->setPixelColor(i,j,*scene->getBackgroundColor());

            }
            else {
                 Vector3<float> normalVector = sceneObject->getNormalVector(crossPoint);
                 Vector3<float> observationVector = directionVector*-1;
                 scene->setPixelColor(i,j, sceneObject->getLocalColor
                                                        (normalVector,
                                                        crossPoint,
                                                        observationVector));
            }
    }
    }
}
