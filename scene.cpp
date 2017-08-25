#include "scene.h"
#include "sceneobject.h"
#include "sphere.h"

Scene* Scene::instance = nullptr;

Scene::Scene()
{
    backgroundColor = new Vector3<float>(1.0, 0.5, 0.5);
    globalAmbient = new Vector3<float>(0.4, 0.4, 0.4);

    lights = nullptr;
    sceneObjects = nullptr;
    numOfLights = 0;
    numOfObjects = 0;

    pixels = nullptr;
}

Scene::~Scene()
{
    delete backgroundColor;
    delete globalAmbient;


    for (int i=0; i<numOfLights; i++) {
        delete lights[i];
    }
    delete [] lights;
    numOfLights = 0 ;

    for (int i=0; i<numOfObjects;i++) {
        delete sceneObjects[i];
    }
    delete [] sceneObjects;
    numOfObjects = 0;

    for (int i = 0; i <  Camera::getInstance()->getPixWidth(); i++) {
        for (int j = 0; j <  Camera::getInstance()->getPixHeight(); j++)
            delete pixels[i][j];
        delete [] pixels[i];
    }
    delete [] pixels;

    instance = nullptr;
}

int Scene::getNumOfObjects()
{
    return numOfObjects;
}

void Scene::addObject(SceneObject *sceneObject)
{
    SceneObject** tempSceneObjects = new SceneObject*[numOfObjects+1];
    std::copy(sceneObjects, sceneObjects+numOfObjects, tempSceneObjects);
    tempSceneObjects[numOfObjects]=sceneObject;
    numOfObjects++;
    delete[] sceneObjects;
    sceneObjects = tempSceneObjects;
}

void Scene::addLight(Light *light)
{
    Light** tempLight = new Light*[numOfLights+1];
    std::copy(lights, lights+numOfLights, tempLight);
    tempLight[numOfLights] = light;
    numOfLights++;
    delete[] lights;
    lights = tempLight;
}

void Scene::setUpPixels()
{
    if(pixels != nullptr) return;
    pixels = new Vector3<float>**[Camera::getInstance()->getPixWidth()];
        for (int i = 0; i < Camera::getInstance()->getPixWidth(); i++) {
            pixels[i] = new Vector3<float>*[Camera::getInstance()->getPixHeight()];
            for (int j = 0; j < Camera::getInstance()->getPixHeight(); j++)
                pixels[i][j] = new Vector3<float>(0.0, 0.0, 0.0);
        }
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
