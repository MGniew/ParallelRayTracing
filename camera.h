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
