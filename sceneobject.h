#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

class SceneObject
{
public:
    SceneObject();
    ~SceneObject();
    virtual float* getPixelColor(float* normalVector) = 0; //returns RGB, uses Phong model
    virtual bool trace(float* crossPoint,
                       float* startPoint,
                       float* directionVector) = 0; //returns true if hit, cordinates in param
    virtual float* getNormalVector(float* crossPoint) = 0;
};

#endif // SCENEOBJECT_H
