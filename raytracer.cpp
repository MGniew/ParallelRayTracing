#include "raytracer.h"
#include "sceneobject.h"
#include "scene.h"

RayTracer::RayTracer()
{
    scene = Scene::getInstance();
    camera = Camera::getInstance();
    buffer = scene->getPixels();
}

void RayTracer::recursiveRayTracer(int depth)
{

    Vector3<float> worldPosOfPixel;
    Vector3<float> directionVector;

    for(int i = 0; i < camera->getPixWidth(); i++) {
        for(int j = 0; j < camera->getPixHeight(); j++) {
            worldPosOfPixel = camera->getWorldPosOfPixel(i,j);
            directionVector = worldPosOfPixel - *camera->getEye();
            directionVector.normalize();
            buffer[i][j]->setValues(getColorRecursive(worldPosOfPixel, directionVector, depth));
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

    if (depth == 0)
        return Vector3<float>();

    depth--;
    sceneObject = getClosest(crossPoint, startPoint, directionVector);
    //nie ma opcji - jakiś promień idzie źle :(
    if (sceneObject == nullptr)
        return Vector3<float>(*scene->backgroundColor);


     Vector3<float> normalVector = sceneObject->getNormalVector(crossPoint);
     Vector3<float> observationVector = directionVector*-1;

     crossPoint = crossPoint + normalVector*0.0001;
     localColor.setValues(sceneObject->getLocalColor
                           (normalVector,
                           crossPoint,
                           observationVector));

     reflectedRay = directionVector.reflect(normalVector);
    reflectedRay.normalize();
     reflectedColor = getColorRecursive(crossPoint, reflectedRay, depth);
     return localColor*.75 + reflectedColor*.25;


}


//check with z Far
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

            sceneObject = getClosest(crossPoint, worldPosOfPixel, directionVector);


            if (sceneObject == nullptr) {
                buffer[i][j]->setValues(*scene->getBackgroundColor());

            }
            else {
                 Vector3<float> normalVector = sceneObject->getNormalVector(crossPoint);
                 Vector3<float> observationVector = directionVector*-1;
                 buffer[i][j]->setValues(sceneObject->getLocalColor
                                                        (normalVector,
                                                        crossPoint,
                                                        observationVector));
            }
    }
    }
}


SceneObject *RayTracer::getClosest(Vector3<float> &crossPoint,
                                   Vector3<float> &startingPoint,
                                   Vector3<float> &directionVector)
{

    Scene* scene = Scene::getInstance();
    Vector3<float> tempCrossPoint;
    SceneObject* sceneObject = nullptr;
    float distance, tempDistance;

    for(int obj = 0; obj < scene->getNumOfObjects(); obj++)
    {
        if ((scene->sceneObjects[obj])->trace(tempCrossPoint, startingPoint, directionVector)) {
            tempDistance = startingPoint.powDistanceFrom(tempCrossPoint);
            if (sceneObject == nullptr) {
                sceneObject = scene->sceneObjects[obj];
                distance = tempDistance;
                crossPoint = tempCrossPoint;
            }
            else {
                if (tempDistance < distance) {
                    distance = tempDistance;
                    sceneObject = scene->sceneObjects[obj];
                    crossPoint = tempCrossPoint;
                }
            }

        }
    }
    return sceneObject;
}

