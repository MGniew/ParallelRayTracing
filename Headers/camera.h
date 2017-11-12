#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"
#include <math.h>
#include "serializable.h"

class Camera : public Serializable
{
public:
    Camera();
    Camera(Vector3<float>* eye,
           Vector3<float>* lookAt,
           float zNear,
           float zFar,
           float povy);
    ~Camera();
    void setUp(int pixWidth, int pixHeight);

    static Camera* instance;
    static Camera* getInstance();
    static Camera* getInstance(Vector3<float>* eye,
                   Vector3<float>* lookAt,
                   float zNear,
                   float zFar,
                   float povy);

    Vector3<float> getWorldPosOfPixel(int x, int y);
    void rotate();

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

    float getPovy();
    void setPovy(float value);

    void serialize(std::vector<char> *bytes);
    void deserialize(const std::vector<char>& bytes);
    char getType();

//private:
    Vector3<float>* eye;
    Vector3<float>* look;
    Vector3<float>* up;
    Vector3<float>* lookAt;

    float zNear;
    float zFar;
    int pixWidth;
    int pixHeight;
    float povy;
    float aspect;
    float worldWidth;
    float worldHeight;

    float R;
    float ver;
    float hor;


};

#endif // CAMERA_H
