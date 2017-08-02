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

