#include "raytracer.h"
#include "sceneobject.h"

RayTracer::RayTracer()
{

}


//check with z Far
void RayTracer::basicRaytracer()
{
    Scene* scene = Scene::getInstance();
    Camera* camera = Camera::getInstance();
    Vector3<float>*** buffer = scene->getPixels();

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
            if (sceneObject == nullptr) {
                sceneObject = scene->sceneObjects[obj];
                distance = startingPoint.powDistanceFrom(tempCrossPoint);
                crossPoint = tempCrossPoint;
            }
            else {
                tempDistance = startingPoint.powDistanceFrom(tempCrossPoint);
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

