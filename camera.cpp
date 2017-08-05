#include "camera.h"
#include <iostream>

Camera* Camera::instance = nullptr;

Camera::Camera(Vector3<float>* eye,
               float rotationX,
               float rotationY,
               float rotationZ,
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
    this->povy = povy;


    this->look = new Vector3<float>(0.0,0.0,1.0);
    this->up = new Vector3<float>(0.0,1.0,0.0);

    //make this a fuction...
    look->rotateX(rotationX);
    look->rotateY(rotationY);
    look->rotateZ(rotationZ);

    up->rotateX(rotationX);
    up->rotateY(rotationY);
    up->rotateZ(rotationZ);

    aspect = pixWidth/pixHeight;
    worldHeight = 2*tan(povy/2) * zNear;
    worldWidth = aspect * worldHeight;
}

Camera::~Camera()
{
    delete eye;
    delete up;
    delete look;
}


Camera *Camera::getInstance(Vector3<float>* eye,
               float rotationX,
               float rotationY,
               float rotationZ,
               float zNear,
               float zFar,
               int pixWidth,
               int pixHeight,
               float povy)
{
    if (instance == nullptr) {
        instance = new Camera(eye, rotationX, rotationY, rotationZ, zNear, zFar, pixWidth, pixHeight, povy);
    }
    return instance;
}

Camera *Camera::getInstance()
{
    return instance;
}

//from up left
Vector3<float> Camera::getWorldPosOfPixel(int x, int y)
{
    //lol look to punkt! debilu...
    //hmm jeszcze coś do poprawy, ale co :)?
    Vector3<float> lookVector = *look;
    Vector3<float> screenCenter = *eye + lookVector.normalize()*zNear;
    Vector3<float> screenWidthVector = up->vectorProduct(lookVector).normalize();
   // Vector3<float> screenHeightVector = screenWidthVector.vectorProduct(lookVector).normalize(); //change to up vec?
    Vector3<float> translationVectorX = (screenWidthVector.normalize() * -(worldWidth/(float)pixWidth)); //przeciwny zwrot
    Vector3<float> translationVectorY = (up->normalize() * -(worldHeight/(float)pixHeight));
    Vector3<float> startingPoint = screenCenter + screenWidthVector * (worldWidth/2) +
                                   *up * (worldHeight/2);

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

