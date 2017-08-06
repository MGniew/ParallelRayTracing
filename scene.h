#ifndef SCENE_H
#define SCENE_H

#include "light.h"
#include "camera.h"
#include "raytracer.h"
#include <iostream>

class SceneObject; //hack circural includes - real include in .cpp
class Sphere;

class Scene
{
public:
    Scene(); //parser from txt?
    ~Scene();

    static Scene* instance;
    Light** Lights;
    SceneObject** sceneObjects;
    Vector3<float>*** pixels; // HxW*3
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
};

#endif // SCENE_H
