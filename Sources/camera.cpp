#include "camera.h"
#include <iostream>

Camera* Camera::instance = nullptr;

Camera::Camera()
{
    serializedSize = 4 * Vector3<float>::serializedSize +
                     9 * sizeof(float) +
                     2 * sizeof(int);

    zNear = 1;
    zFar = 15;
    pixHeight = 500;
    pixWidth = 700;
    eye = new Vector3<float>(0,0,-1);
    povy = 70;
    look = new Vector3<float>(0, 0, 1);
    up = new Vector3<float>(0, 1, 0);
    lookAt = new Vector3<float>(0,0,0);
}

Camera::Camera(Vector3<float>* eye,
               Vector3<float>* lookAt,
               float zNear,
               float zFar,
               float povy) {

    serializedSize = 4 * Vector3<float>::serializedSize +
                     9 * sizeof(float) +
                     2 * sizeof(int);

    this->zNear = zNear;
    this->zFar = zFar;
    this->eye = eye;
    this->povy = povy;
    this->lookAt = lookAt;
    look = nullptr;
    up = nullptr;
}

Camera::~Camera()
{
    delete eye;
    delete up;
    delete look;
    delete lookAt;
}

void Camera::setUp(int pixWidth, int pixHeight)
{
    delete look;
    delete up;

    this->pixHeight = pixHeight;
    this->pixWidth = pixWidth;

    Vector3<float> lookVec = *lookAt - *eye;
    lookVec.normalize();
    this->look = new Vector3<float>(lookVec);

    this->up = new Vector3<float>(0.0,1.0,0.0);
    *up = (look->vectorProduct(*up)).vectorProduct(*look);
    up->normalize();

    aspect = (float)pixWidth/pixHeight;
    povy = povy * M_PI/180;
    worldHeight = 2*tan(povy/2) * zNear;
    worldWidth = aspect * worldHeight;

    R = lookAt->distanceFrom(*eye);
    if (R == 0) {
        ver = 0;
        hor = 0;
    } else {
        ver = asin((eye->y)/R);
        int tmp;
        if (ver == 0) {
            tmp = R;
        } else {
            tmp = cos(ver) * R;
        }
        hor = asin((eye->z)/tmp);
    }

    while (ver < 0){
        ver += 2 * M_PI;
    }

    while (hor < 0) {
        hor += 2 * M_PI;
    }
}


Camera *Camera::getInstance(Vector3<float>* eye,
               Vector3<float>* lookAt,
               float zNear,
               float zFar,
               float povy)
{
    if (instance != nullptr) {
        delete instance;
    }
    instance = new Camera(eye, lookAt, zNear, zFar, povy);
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

void Camera::rotate()
{
    hor += M_PI/720;
    if (hor >= 2 * M_PI)
        hor = 0;
    //calculate next eye pos
    eye->x = R * cos(hor) * cos (ver);
    eye->z = R * sin(hor) * cos (ver);

    //calculate new look vector
    *look = *lookAt - *eye;
    look->normalize();

    //calculate new up vector;
    up->setValues(0.0,1.0,0.0);
    *up = (look->vectorProduct(*up)).vectorProduct(*look);
    up->normalize();
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
    lookAt->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();

    memcpy(ptr, &R, sizeof(R)); ptr += sizeof(R);
    memcpy(ptr, &ver, sizeof(ver)); ptr += sizeof(ver);
    memcpy(ptr, &hor, sizeof(hor)); ptr += sizeof(hor);
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
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    lookAt->deserialize(vec);

    memcpy(&R, ptr, sizeof(R)); ptr += sizeof(R);
    memcpy(&ver, ptr, sizeof(ver)); ptr += sizeof(ver);
    memcpy(&hor, ptr, sizeof(hor)); ptr += sizeof(hor);
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

