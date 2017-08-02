#ifndef SCENE_H
#define SCENE_H

#include "light.h"
#include "sceneobject.h"

class Scene
{
public:
    Scene(); //parser from txt?
    ~Scene();

    static Scene* instance;
    Light** Lights;
    SceneObject** sceneObjects;
    int*** pixels; // HxW*3
    int* backgroundColor;

    static Scene* getInstance();
    void loadScene (char* file);

};

#endif // SCENE_H
