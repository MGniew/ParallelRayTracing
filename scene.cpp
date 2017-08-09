#include "scene.h"
#include "sceneobject.h"
#include "sphere.h"

Scene* Scene::instance = nullptr;

Scene::Scene()
{
    backgroundColor = new Vector3<float>(1.0, 0.5, 0.5);
    globalAmbient = new Vector3<float>(0.4, 0.4, 0.4);

    Lights = new Light*[1];
    Lights[0] = new Light();
    numOfLights = 1;
    std::cout << "lights are ready" << std::endl;

    sceneObjects = new SceneObject*[5];
    sceneObjects[0] = new Sphere(new Vector3<float>(.7, 0.3, .5),
                                 new Vector3<float>(0.6, 0.7, 0.8),
                                 new Vector3<float>(0.8, 0.8, 0.8),
                                 10.0,
                                 new Vector3<float>(0, 0.0, 0.0),
                                 10.0,
                                 0, .7, 0.3,
                                 1.5);

    sceneObjects[1] = new Sphere(new Vector3<float>(.3, 0.4, 0.4),
                                 new Vector3<float>(0.6, 0.7, 0.8),
                                 new Vector3<float>(0.8, 0.8, 0.8),
                                 55.0,
                                 new Vector3<float>(-0.5, 0.0, 2.0),
                                 1.0,
                                 0, 0.2, 0.8,
                                 1.5);

    sceneObjects[2] = new Sphere(new Vector3<float>(.7, 0.7, 0.4),
                                 new Vector3<float>(0.6, 0.7, 0.8),
                                 new Vector3<float>(0.8, 0.8, 0.8),
                                 70.0,
                                 new Vector3<float>(1.5, 0.0, 2.0),
                                 .5,
                                 0, 0.2, 0.8,
                                 1.5);

    sceneObjects[3] = new Sphere(new Vector3<float>(0.3, 0.2, 1.0),
                                 new Vector3<float>(0.9, 0.9, 0.9),
                                 new Vector3<float>(0.9, 0.5, 0.5),
                                 10.0,
                                 new Vector3<float>(0.0, 1, 0.4),
                                 2,
                                 0.8, 0.0, 0.2,
                                 3);

    sceneObjects[4] = new Sphere(new Vector3<float>(1.0, 0.4, 0.4),
                                 new Vector3<float>(0.9, 0.9, 0.9),
                                 new Vector3<float>(0.9, 0.5, 0.5),
                                 50.0,
                                 new Vector3<float>(0.0, 0.0, 7.0),
                                 4,
                                 0, 0.2, 0.8,
                                 1.5);
    numOfObjects = 5;

    std::cout << "Objects are ready" << std::endl;

    pixels = new Vector3<float>**[Camera::getInstance()->getPixWidth()];
    for (int i = 0; i < Camera::getInstance()->getPixWidth(); i++) {
        pixels[i] = new Vector3<float>*[Camera::getInstance()->getPixHeight()];
        for (int j = 0; j < Camera::getInstance()->getPixHeight(); j++)
            pixels[i][j] = new Vector3<float>(0.0, 0.0, 0.0);
    }
    std::cout << "pixel array created" << std::endl;

}

Scene::~Scene()
{
    delete backgroundColor;
    delete globalAmbient;

    delete Lights[0];
    delete [] Lights;
    numOfLights = 0 ;

    delete sceneObjects[0];
    delete sceneObjects[1];
    delete sceneObjects[2];
    delete sceneObjects[3];
    delete sceneObjects[4];
    delete [] sceneObjects;
    numOfObjects = 0;

    for (int i = 0; i <  Camera::getInstance()->getPixWidth(); i++) {
        for (int j = 0; j <  Camera::getInstance()->getPixHeight(); j++)
            delete pixels[i][j];
        delete [] pixels[i];
    }
    delete [] pixels;

    instance = nullptr;
    std::cout << "bye scene" << std::endl;

}

int Scene::getNumOfObjects()
{
    return numOfObjects;
}

int Scene::getNumOfLights()
{
    return numOfLights;
}

Vector3<float> ***Scene::getPixels()
{
    return pixels;
}

Vector3<float> *Scene::getGlobalAmbient()
{
    return globalAmbient;
}

void Scene::setGlobalAmbient(float r, float g, float b)
{
    backgroundColor->x = r;
    backgroundColor->y = g;
    backgroundColor->z = b;
}

Scene *Scene::getInstance()
{
    if (instance == nullptr)
        instance = new Scene();
    return instance;
}

Vector3<float>* Scene::getBackgroundColor()
{
    return backgroundColor;
}

void Scene::setBackgroundColor(float r, float g, float b)
{
    backgroundColor->x = r;
    backgroundColor->y = g;
    backgroundColor->z = b;
}
