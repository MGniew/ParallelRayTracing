#include "camera.h"

Camera* Camera::instance = NULL;

Camera::Camera(float *eye, float *look, float *up, float zNear, float zFar, int pixWidth, int pixHeight)
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

float *Camera::getEye()
{
    return eye;
}

void Camera::setEye(float *value)
{
    eye = value;
}

float *Camera::getLook()
{
    return look;
}

void Camera::setLook(float *value)
{
    look = value;
}

float *Camera::getUp()
{
    return up;
}

void Camera::setUp(float *value)
{
    up = value;
}

