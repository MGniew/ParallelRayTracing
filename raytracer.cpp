#include "raytracer.h"

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
    std::list<SceneObject*> listOfHitObjects;
    bool inters;
    float distance;
    //for every pixel
    for(int i = 0; i < camera->getPixWidth(); i++) {
        for(int j = 0; j < camera->getPixHeight(); j++) {

            //get ray
            worldPosOfPixel = camera->getWorldPosOfPixel(i,j);

            directionVector = worldPosOfPixel - *camera->getEye();
            directionVector.normalize();


            //find objects intersect with ray
            for(int obj = 0; obj < scene->getNumOfObjects(); obj++)
            {
                if ((scene->sceneObjects[obj])->trace(crossPoint, worldPosOfPixel, directionVector)) {
                    listOfHitObjects.push_back(scene->sceneObjects[obj]);
                }
            }

            scene->sceneObjects[0]->getAmb();
            if (listOfHitObjects.empty()) {
                buffer[i][j]->setValues(*scene->getBackgroundColor());

            }
            else {
                 Vector3<float> normalVector = listOfHitObjects.front()->getNormalVector(crossPoint);
                 Vector3<float> observationVector = directionVector*-1;
                 buffer[i][j]->setValues(listOfHitObjects.front()->getLocalColor
                                                        (normalVector,
                                                        crossPoint,
                                                        observationVector));


            }

            listOfHitObjects.clear();

    }
    }



}

