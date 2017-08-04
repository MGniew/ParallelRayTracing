#include "camera.h"

Camera* Camera::instance = nullptr;

Camera::Camera(Vector3<float>* eye,
               Vector3<float>* look,
               Vector3<float>* up,
               float zNear,
               float zFar,
               int pixWidth,
               int pixHeight,
               float povy) {

    this->zNear = zNear;
    this->zFar = zFar;
    this->pixHeight = pixHeight;
    this->pixWidth = pixWidth;
    this->eye = eye;
    this->look = look;
    this->up = up;
    this->povy = povy;

    aspect = pixWidth/pixHeight;
    worldHeight = 2*tan(povy/2) * zNear;
    worldWidth = aspect * worldHeight;
}

Camera *Camera::getInstance()
{
    return instance;
}

//from up left
Vector3<float> Camera::getWorldPosOfPixel(int x, int y)
{
    Vector3<float> screenCenter = *eye + look->normalize()*zNear;
    Vector3<float> screenWidthVector = up->vectorProduct(*look).normalize();
    Vector3<float> screenHeightVector = screenWidthVector.vectorProduct(*look); //change to up vec?
    Vector3<float> translationVectorX = (screenWidthVector * -(worldWidth/(float)pixWidth)).normalize(); //przeciwny zwrot
    Vector3<float> translationVectorY = (screenHeightVector * -(worldHeight/(float)pixHeight)).normalize();
    Vector3<float> startingPoint = screenCenter + screenWidthVector * (worldWidth/2) +
                                   screenHeightVector * (worldHeight/2);

    return startingPoint + translationVectorX*x + translationVectorY*y;

}



float Camera::getZNear()
{
    return zNear;
}

void Camera::setZNear(float value)
{
    zNear = value;
}

float Camera::getZFar()
{
    return zFar;
}

void Camera::setZFar(float value)
{
    zFar = value;
}

int Camera::getPixWidth()
{
    return pixWidth;
}

void Camera::setPixWidth(int value)
{
    pixWidth = value;
}

int Camera::getPixHeight()
{
    return pixHeight;
}

void Camera::setPixHeight(int value)
{
    pixHeight = value;
}

Vector3<float>* Camera::getEye()
{
    return eye;
}

void Camera::setEye(Vector3<float>* value)
{
    eye = value;
}

Vector3<float>* Camera::getLook()
{
    return look;
}

void Camera::setLook(Vector3<float>* value)
{
    look = value;
}

Vector3<float>* Camera::getUp()
{
    return up;
}

void Camera::setUp(Vector3<float>* value)
{
    up = value;
}

float Camera::getPovy()
{
    return povy;
}

void Camera::setPovy(float value)
{
    povy = value;
}

