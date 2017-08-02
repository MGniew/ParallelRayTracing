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



    float getSpecShin();
    void setSpecShin(float value);

    float *getSpec();
    void setSpec(float *value);

    float *getDif();
    void setDif(float *value);

    float *getAmb();
    void setAmb(float *value);

private:
    float* amb;
    float* dif;
    float* spec;
    float specShin;
};

#endif // SCENEOBJECT_H
