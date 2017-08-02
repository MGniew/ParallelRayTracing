#ifndef CAMERA_H
#define CAMERA_H

#include <array>

class Camera
{
public:
    Camera(float* eye,
           float* look,
           float* up,
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

    float *getEye();
    void setEye(float *value);

    float *getLook();
    void setLook(float *value);

    float *getUp();
    void setUp(float *value);

private:
    float* eye;
    float* look;
    float* up;

    float zNear;
    float zFar;
    int pixWidth;
    int pixHeight;
};

#endif // CAMERA_H
