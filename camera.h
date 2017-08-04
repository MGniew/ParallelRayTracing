#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"

class Camera
{
public:
    Camera(Vector3<float>* eye,
           Vector3<float>* look,
           Vector3<float>* up,
           float zNear,
           float zFar,
           int pixWidth,
           int pixHeight);
    ~Camera();

    static Camera* instance;
    static Camera* getInstance();

    float getZNear();
    void setZNear(float value);

    float getZFar();
    void setZFar(float value);

    int getPixWidth();
    void setPixWidth(int value);

    int getPixHeight();
    void setPixHeight(int value);

    Vector3<float>* getEye();
    void setEye(Vector3<float>* value);

    Vector3<float>* getLook();
    void setLook(Vector3<float>* value);

    Vector3<float>* getUp();
    void setUp(Vector3<float>* value);

private:
    Vector3<float>* eye;
    Vector3<float>* look;
    Vector3<float>* up;

    float zNear;
    float zFar;
    int pixWidth;
    int pixHeight;
};

#endif // CAMERA_H
