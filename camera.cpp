#include "camera.h"
#include <iostream>

Camera* Camera::instance = nullptr;

Camera::Camera()
{
    zNear = 1;
    zFar = 15;
    pixHeight = 500;
    pixWidth = 700;
    eye = new Vector3<float>(0,0,0);
    povy = 70;
    look = nullptr;
    up = nullptr;
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
    setUp();
}

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
    this->rotationX = rotationX;
    this->rotationY = rotationY;
    this->rotationZ = rotationZ;
    look = nullptr;
    up = nullptr;

    setUp();

}

Camera::~Camera()
{
    delete eye;
    delete up;
    delete look;
}

void Camera::setUp()
{

    serializedSize = 3 * Vector3<float>::serializedSize +
                     9 * sizeof(float) +
                     2 * sizeof(int);

    delete look;
    delete up;

    this->look = new Vector3<float>(0.0,0.0,1.0);
    this->up = new Vector3<float>(0.0,1.0,0.0);

    look->rotateX(rotationX);
    look->rotateY(rotationY);
    look->rotateZ(rotationZ);

    up->rotateX(rotationX);
    up->rotateY(rotationY);
    up->rotateZ(rotationZ);

    aspect = (float)pixWidth/pixHeight;
    povy = povy * M_PI/180;
    worldHeight = 2*tan(povy/2) * zNear;
    worldWidth = aspect * worldHeight;
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
    if (instance != nullptr) {
        delete instance;
    }
    instance = new Camera(eye, rotationX, rotationY, rotationZ, zNear, zFar, pixWidth, pixHeight, povy);
    return instance;
}

Camera *Camera::getInstance()
{
    if (instance == nullptr)
        instance = new Camera();
    return instance;
}

//from up left
Vector3<float> Camera::getWorldPosOfPixel(int x, int y)
{

    Vector3<float> lookVector = *look;
    Vector3<float> screenCenter = *eye + lookVector.normalize()*zNear;
    Vector3<float> screenWidthVector = up->vectorProduct(lookVector).normalize();
    Vector3<float> translationVectorX = (screenWidthVector.normalize() * -(worldWidth/(float)pixWidth));
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

void Camera::serialize(std::vector<char> *bytes)
{
    bytes->resize(serializedSize);
    char *ptr = bytes->data();
    std::vector<char> vec;
    eye->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    look->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    up->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();

    memcpy(ptr, &rotationX, sizeof(rotationX)); ptr += sizeof(rotationX);
    memcpy(ptr, &rotationY, sizeof(rotationY)); ptr += sizeof(rotationY);
    memcpy(ptr, &rotationZ, sizeof(rotationZ)); ptr += sizeof(rotationZ);
    memcpy(ptr, &zNear, sizeof(zNear)); ptr += sizeof(zNear);
    memcpy(ptr, &zFar, sizeof(zFar)); ptr += sizeof(zFar);
    memcpy(ptr, &pixWidth, sizeof(pixWidth)); ptr += sizeof(pixWidth);
    memcpy(ptr, &pixHeight, sizeof(pixHeight)); ptr += sizeof(pixHeight);
    memcpy(ptr, &povy, sizeof(povy)); ptr += sizeof(povy);
    memcpy(ptr, &aspect, sizeof(aspect)); ptr += sizeof(aspect);
    memcpy(ptr, &worldHeight, sizeof(worldHeight)); ptr += sizeof(worldHeight);
    memcpy(ptr, &worldWidth, sizeof(worldWidth));
}

void Camera::deserialize(const std::vector<char> &bytes)
{
    const char* ptr = bytes.data();
    std::vector<char> vec;
    vec.resize(Vector3<float>::serializedSize);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    eye->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    look->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    up->deserialize(vec);

    memcpy(&rotationX, ptr, sizeof(rotationX)); ptr += sizeof(rotationX);
    memcpy(&rotationY, ptr, sizeof(rotationY)); ptr += sizeof(rotationY);
    memcpy(&rotationZ, ptr, sizeof(rotationZ)); ptr += sizeof(rotationZ);
    memcpy(&zNear, ptr, sizeof(zNear)); ptr += sizeof(zNear);
    memcpy(&zFar, ptr, sizeof(zFar)); ptr += sizeof(zFar);
    memcpy(&pixWidth, ptr, sizeof(pixWidth)); ptr += sizeof(pixWidth);
    memcpy(&pixHeight, ptr, sizeof(pixHeight)); ptr += sizeof(pixHeight);
    memcpy(&povy, ptr, sizeof(povy)); ptr += sizeof(povy);
    memcpy(&aspect, ptr, sizeof(aspect)); ptr += sizeof(aspect);
    memcpy(&worldHeight, ptr, sizeof(worldHeight)); ptr += sizeof(worldHeight);
    memcpy(&worldWidth, ptr, sizeof(worldWidth));

}

char Camera::getType()
{
    return 'c';
}

