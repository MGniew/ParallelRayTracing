#include "scene.h"
#include "sceneobject.h"
#include "sphere.h"

Scene* Scene::instance = nullptr;

Scene::Scene()
{
    backgroundColor = new Vector3<float>(0.5, 0.5, 0.5);
    globalAmbient = new Vector3<float>(0.5, 0.5, 0.5);

    Lights = new Light*[1];
    Lights[0] = new Light();
    std::cout << "lights are ready" << std::endl;

    sceneObjects = new SceneObject*[1];
    sceneObjects[0] = new Sphere(new Vector3<float>(0.8, 0.8, 0.8),
                                 new Vector3<float>(0.6, 0.7, 0.8),
                                 new Vector3<float>(1.0, 1.0, 1.0),
                                 30.0,
                                 new Vector3<float>(0.0, 0.0, 3.0),
                                 1.0);

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

    delete sceneObjects[0];
    delete [] sceneObjects;

    for (int i = 0; i <  Camera::getInstance()->getPixWidth(); i++) {
        for (int j = 0; j <  Camera::getInstance()->getPixHeight(); j++)
            delete pixels[i][j];
        delete [] pixels[i];
    }
    delete [] pixels;

    instance = nullptr;
    std::cout << "bye scene" << std::endl;

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
