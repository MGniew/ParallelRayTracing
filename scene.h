#ifndef SCENE_H
#define SCENE_H

#include "light.h"
#include "camera.h"
#include "raytracer.h"
#include <iostream>
#include "pixels.h"

class SceneObject;
class Sphere;

class Scene
{
public:
    Scene();
    ~Scene();

    static Scene* instance;
    Light** lights;
    SceneObject** sceneObjects;
    //Vector3<float>*** pixels; // HxW*3
    Pixels* pixels;
    Vector3<float>* backgroundColor;
    Vector3<float>* globalAmbient;
    int numOfLights;
    int numOfObjects;

    static Scene* getInstance();
    void loadScene (char* file);

    Vector3<float>* getBackgroundColor();
    void setBackgroundColor(float r, float g, float b);

    Vector3<float> *getGlobalAmbient();
    void setGlobalAmbient(float r, float g, float b);

    Vector3<float> ***getPixels();
    int getNumOfLights();
    int getNumOfObjects();
    void addObject(SceneObject* sceneObject);
    void addLight(Light* light);
    void setUpPixels(int x, int y);
    int getStartX();
    int getStartY();
    int getWidth();
    int getHeight();
};

#endif // SCENE_H
