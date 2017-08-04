#ifndef SCENE_H
#define SCENE_H

#include "light.h"
class SceneObject; //hack circural includes - real include in .cpp

class Scene
{
public:
    Scene(); //parser from txt?
    ~Scene();

    static Scene* instance;
    Light** Lights;
    SceneObject** sceneObjects;
    int*** pixels; // HxW*3
    Vector3<float>* backgroundColor;
    Vector3<float>* globalAmbient;

    static Scene* getInstance();
    void loadScene (char* file);

    Vector3<float>* getBackgroundColor();
    void setBackgroundColor(float r, float g, float b);

    Vector3<float> *getGlobalAmbient();
    void setGlobalAmbient(float r, float g, float b);
};

#endif // SCENE_H
