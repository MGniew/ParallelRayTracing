#ifndef SCENE_H
#define SCENE_H

#include "light.h"
#include "camera.h"
#include "raytracer.h"
#include <iostream>
#include "pixels.h"
#include "serializable.h"


class SceneObject;
class Sphere;
class Triangle;
class BSP;

class Scene : public Serializable
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
    BSP* bsp;

    static Scene* getInstance();
    void loadScene (char* file);

    Vector3<float>* getBackgroundColor();
    void setBackgroundColor(float r, float g, float b);

    Vector3<float> *getGlobalAmbient();
    void setGlobalAmbient(float r, float g, float b);

    void buildBSP(int depth);

    unsigned char *getPixels();
    int getNumOfLights();
    int getNumOfObjects();
    void addObject(SceneObject* sceneObject);
    void addLight(Light* light);
    void setUpPixels(int x, int y);
    int getStartX();
    int getStartY();
    int getWidth();
    int getHeight();
    SceneObject* getClosest(Vector3<float> &crossPoint, Vector3<float> &startPoint, Vector3<float> &directionVector);
    bool isInShadow(Vector3<float> &crossPoint, Vector3<float> &directionVector, Vector3<float> &lightPos);
    void setPixelColor(int x, int y, Vector3<float> color);

    void serialize(std::vector<char> *bytes);
    void deserialize(const std::vector<char>& bytes);
    char getType();    
    void print();

    bool useShadows;
    void setShadowsUsage(bool a);
    bool useBSP;
    void setBSPUsage(bool a);
};

#endif // SCENE_H
