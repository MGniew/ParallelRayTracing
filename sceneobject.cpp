#include "sceneobject.h"
#include "vector3.h"
#include "bsp.h"

SceneObject::SceneObject()
{

}


SceneObject::SceneObject(Vector3<float>* amb,
                         Vector3<float>* dif,
                         Vector3<float>* spec,
                         float specShin,
                         float transparency,
                         float mirror,
                         float local,
                         float density){
    this->amb = amb;
    this->dif = dif;
    this->spec = spec;
    this->specShin = specShin;
    this->transparency= transparency;
    this->mirror = mirror;
    this->local = local;
    if (density < 1)
        density = 1;
    this->density = density;

}

SceneObject::~SceneObject()
{
    delete spec;
    delete dif;
    delete amb;
}

Vector3<float> SceneObject::getLocalColor(Vector3<float> &normalVector,
                                          Vector3<float> &crossPoint,
                                          Vector3<float> &observationVector)
{
    Scene* scene = Scene::getInstance();
    Vector3<float> returnColor = amb->multiplyByVector(*scene->getGlobalAmbient());
    for (int i=0; i<scene->getNumOfLights(); i++) {
        Vector3<float>* lightPossition = scene->lights[i]->pos;
        Vector3<float> lightVector = *lightPossition - crossPoint;
        lightVector.normalize();
        float n_dot_l = lightVector.scalarProduct(normalVector);
        Vector3<float> reflectionVector = (lightVector*-1).reflect(normalVector);
        reflectionVector.normalize();
        float v_dot_r = reflectionVector.scalarProduct(observationVector);
        if (v_dot_r < 0)
            v_dot_r = 0;

     // if (n_dot_l > 0 && !isInShadow(crossPoint, lightVector, *lightPossition)) {
        if (n_dot_l > 0 && !isInShadowBSP(crossPoint, lightVector, *lightPossition)) {
            returnColor += (dif->multiplyByVector(*scene->lights[i]->dif))*n_dot_l +
                    spec->multiplyByVector(*scene->lights[i]->spec)*pow(double(v_dot_r), specShin) +
                    amb->multiplyByVector(*scene->lights[i]->amb);
            //(float)(1/(1 + 0.01*sqrt(distance) + 0.001*distance)))
        }
    }
    return returnColor;
}

bool SceneObject::isInShadow(Vector3<float> &crossPoint, Vector3<float> &directionVector, Vector3<float> &lightPos)
{
    Scene* scene = Scene::getInstance();
    Vector3<float> tempCrossPoint;
    float LightDistance = crossPoint.distanceFrom(lightPos);
    float dist;

    for(int obj = 0; obj < scene->getNumOfObjects(); obj++){
        if ((scene->sceneObjects[obj])->trace(tempCrossPoint, crossPoint, directionVector, dist)) {
           if (dist < LightDistance)
           return true;
        }
    }
    return false;
}

bool SceneObject::isInShadowBSP(Vector3<float> &crossPoint, Vector3<float> &directionVector, Vector3<float> &lightPos)
{
    Scene* scene = Scene::getInstance();
    return scene->bsp->isInShadow(crossPoint, directionVector, lightPos);
}

float SceneObject::getSpecShin()
{
    return specShin;
}

void SceneObject::setSpecShin(float value)
{
    specShin = value;
}

Vector3<float>* SceneObject::getSpec()
{
    return spec;
}

void SceneObject::setSpec(float r, float g, float b)
{
    spec->x = r;
    spec->y = g;
    spec->z = b;
}

Vector3<float>* SceneObject::getDif()
{
    return dif;
}

void SceneObject::setDif(float r, float g, float b)
{
    dif->x = r;
    dif->y = g;
    dif->z = b;
}

Vector3<float>* SceneObject::getAmb()
{
    return amb;
}

void SceneObject::setAmb(float r, float g, float b)
{
    amb->x = r;
    amb->y = g;
    amb->z = b;
}

float SceneObject::getTransparency()
{
    return transparency;
}

void SceneObject::setTransparency(float value)
{
    transparency = value;
}

float SceneObject::getMirror()
{
    return mirror;
}

void SceneObject::setMirror(float value)
{
    mirror = value;
}

float SceneObject::getLocal()
{
    return local;
}

void SceneObject::setLocal(float value)
{
    local = value;
}

float SceneObject::getDensity()
{
    return density;
}

void SceneObject::setDensity(float value)
{
    density = value;
}
