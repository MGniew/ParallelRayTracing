#include "scene.h"
#include "sceneobject.h"

Scene* Scene::instance = nullptr;

Scene::Scene()
{
    backgroundColor = new Vector3<float>(0.5, 0.5, 0.5);

}

Scene::~Scene()
{
    delete backgroundColor;
}

Scene *Scene::getInstance()
{
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
