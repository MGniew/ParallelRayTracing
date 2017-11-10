#include "scene.h"
#include "sceneobject.h"
#include "sphere.h"
#include "triangle.h"
#include "bsp.h"

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
    bsp = nullptr;

    useBSP = false;
    useShadows = false;

    serializedSize = 2 * Vector3<float>::serializedSize + 2 * sizeof(bool);
}

Scene::~Scene()
{
    delete backgroundColor;
    delete globalAmbient;
    delete bsp;

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

    delete pixels;
    pixels = nullptr;

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

    serializedSize += sceneObject->serializedSize + sizeof(char);
}

void Scene::addLight(Light *light)
{
    Light** tempLight = new Light*[numOfLights+1];
    std::copy(lights, lights+numOfLights, tempLight);
    tempLight[numOfLights] = light;
    numOfLights++;
    delete[] lights;
    lights = tempLight;

    serializedSize += light->serializedSize + sizeof(char);
}

void Scene::setUpPixels(int x, int y)
{
    delete pixels;
    pixels = new Pixels(x,y);
}

int Scene::getStartX()
{
    return pixels->startx;
}

int Scene::getStartY()
{
    return pixels->starty;
}

int Scene::getWidth()
{
    return pixels->x;
}


int Scene::getHeight()
{
    return pixels->y;
}

SceneObject *Scene::getClosest(Vector3<float> &crossPoint, Vector3<float> &startPoint, Vector3<float> &directionVector)
{
    if (useBSP) {
        return bsp->getClosest(crossPoint, startPoint, directionVector);
    }

    Vector3<float> tempCrossPoint;
    SceneObject* sceneObject = nullptr;
    float distance, tempDistance;

    for(int obj = 0; obj < getNumOfObjects(); obj++)
    {
        if ((sceneObjects[obj])->trace(tempCrossPoint, startPoint, directionVector, tempDistance)) {
            if (sceneObject == nullptr) {
                sceneObject = sceneObjects[obj];
                distance = tempDistance;
                crossPoint = tempCrossPoint;
            }
            else {
                if (tempDistance < distance) {
                    distance = tempDistance;
                    sceneObject = sceneObjects[obj];
                    crossPoint = tempCrossPoint;
                }
            }

        }
    }
    return sceneObject;


}

bool Scene::isInShadow(Vector3<float> &crossPoint, Vector3<float> &directionVector, Vector3<float> &lightPos)
{
    if (!useShadows) {
        return false;
    }

    if (useBSP) {
        return bsp->isInShadow(crossPoint, directionVector, lightPos);
    }

    Vector3<float> tempCrossPoint;
    float LightDistance = crossPoint.distanceFrom(lightPos);
    float dist;

    for(int obj = 0; obj < getNumOfObjects(); obj++){
        if ((sceneObjects[obj])->trace(tempCrossPoint, crossPoint, directionVector, dist)) {
           if (dist < LightDistance)
           return true;
        }
    }
    return false;
}

void Scene::setPixelColor(int x, int y, Vector3<float> color)
{
    pixels->setPixel(x, y, color);
}

void Scene::serialize(std::vector<char> *bytes)
{
    bytes->resize(serializedSize);
    char* ptr = bytes->data();
    std::vector<char> vec;
    backgroundColor->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    globalAmbient->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    memcpy(ptr, &useBSP, sizeof(bool)); ptr += sizeof(bool);
    memcpy(ptr, &useShadows, sizeof(bool)); ptr += sizeof(bool);

    //objects
    char type;
    for (int i=0; i<numOfObjects; i++) {
        type = sceneObjects[i]->getType();
        vec.resize(sceneObjects[i]->serializedSize);
        sceneObjects[i]->serialize(&vec);
        memcpy(ptr, &type, sizeof(type)); ptr += sizeof(type);
        memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    }

    //lights
    for (int i=0; i<numOfLights; i++) {
        type = lights[i]->getType();
        vec.resize(lights[i]->serializedSize);
        lights[i]->serialize(&vec);
        memcpy(ptr, &type, sizeof(type)); ptr += sizeof(type);
        memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();

    }

}

void Scene::deserialize(const std::vector<char> &bytes)
{
    const char* ptr = bytes.data();
    std::vector<char> vec;
    vec.resize(Vector3<float>::serializedSize);

    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    backgroundColor->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    globalAmbient->deserialize(vec);
    memcpy(&useBSP, ptr, sizeof(bool)); ptr += sizeof(bool);
    memcpy(&useShadows, ptr, sizeof(bool)); ptr += sizeof(bool);

    char type;
    const char* lastElementPtr = &bytes.back();
    Sphere* sphere;
    Triangle* triangle;
    Light* light;
    while (ptr < lastElementPtr) {
        memcpy(&type, ptr, sizeof(type)); ptr += sizeof(type);
        switch(type) {

            case 't':
                triangle = new Triangle();
                vec.resize(triangle->serializedSize);
                memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
                triangle->deserialize(vec);
                addObject(triangle);
                break;
            case 's':
                sphere = new Sphere();
                vec.resize(sphere->serializedSize);
                memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
                sphere->deserialize(vec);
                addObject(sphere);
                break;
            case 'l':
                light = new Light();
                vec.resize(light->serializedSize);
                memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
                light->deserialize(vec);
                addLight(light);
                break;
        }

    }

}

char Scene::getType()
{
    return 's';
}

void Scene::print()
{
    for(int i =0; i<numOfObjects;i++)
        sceneObjects[i]->print();

    for(int i=0;i<numOfLights;i++)
        lights[i]->print();
}

void Scene::setBSPUsage(bool a)
{
    useBSP = a;
}

void Scene::setShadowsUsage(bool a)
{
    useShadows = a;
}


int Scene::getNumOfLights()
{
    return numOfLights;
}

unsigned char* Scene::getPixels()
{
    return pixels->data;
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

void Scene::buildBSP(int depth)
{
    delete bsp;
    bsp = new BSP();
    bsp->build(bsp->tree, bsp->polygons, depth);
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
