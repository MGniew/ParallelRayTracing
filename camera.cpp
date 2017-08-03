#include "camera.h"

Camera* Camera::instance = nullptr;

Camera::Camera(Vector3<float>* eye, Vector3<float>* look, Vector3<float>* up, float zNear, float zFar, int pixWidth, int pixHeight)
{
    this->zNear = zNear;
    this->zFar = zFar;
    this->pixHeight = pixHeight;
    this->pixWidth = pixWidth;
    this->eye = eye;
    this->look = look;
    this->up = up;
}

Camera::~Camera()
{

}

Camera *Camera::getInstance()
{
    return instance;
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

