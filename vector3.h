#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>
#include "vector"
#include <stdio.h>
#include <string.h>
#include "serializable.h"
#include "iostream"

template <typename type>
class Vector3 : public Serializable
{
public:
    Vector3() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Vector3(type x, type y, type z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3(const Vector3& v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    }

    type x;
    type y;
    type z;
    static const int serializedSize =
            sizeof(type) +
            sizeof(type) +
            sizeof(type);

    Vector3 operator +(const Vector3& v)
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator +=(const Vector3& v)
    {
        x+=v.x;
        y+=v.y;
        z+=v.z;
        return *this;
    }

    Vector3 operator -(const Vector3& v)
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator *(const float& v) {
        return Vector3(v*x, v*y, v*z);
    }

    Vector3 operator /(const float& v) {
        return Vector3(x/v, y/v, z/v);
    }

    Vector3 normalize()
    {
        float d = x*x + y*y + z*z;
        d = sqrt(d);
        x/=d;
        y/=d;
        z/=d;
        return Vector3(x, y, z);
    }

    float scalarProduct(Vector3 &v){
        return x*v.x + y*v.y + z*v.z;
    }

    Vector3 vectorProduct(Vector3 &v) {
        return Vector3(y*v.z -  z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }

    Vector3 multiplyByVector(Vector3 &v) {
        return Vector3(x*v.x, y*v.y, z*v.z);
    }

    void setValues(type x, type y, type z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void setValues(const Vector3 &v){
        x = v.x;
        y = v.y;
        z = v.z;
    }

    //rotation matrix
    void rotateX(float alpha){
        alpha = alpha * M_PI/180;
        y = cos(alpha)*y + -sin(alpha)*z;
        z = sin(alpha)*y + cos(alpha)*z;
    }

    void rotateY(float alpha){
        alpha = alpha * M_PI/180;
        x = cos(alpha)*x + sin(alpha) * z;
        z = -sin(alpha)*x + cos(alpha) * z;
    }

    void rotateZ(float alpha) {
        alpha = alpha * M_PI/180;
        x = cos(alpha)*x + -sin(alpha)*y;
        y = sin(alpha)*x + cos(alpha)*y;
    }

    float powDistanceFrom(Vector3 &v){
        return pow(x - v.x,2) + pow(y - v.y, 2) + pow(z - v.z,2);
    }
//no need to change normal vector dir !
    Vector3<float> reflect(Vector3 &n) {
        float n_dot_l = this->scalarProduct(n);
        return *this - n*(2*n_dot_l);
    }

    Vector3<float> refract(Vector3 &normalVector, float a, float b) {
        Vector3<float> n = normalVector;
        float cosa = this->scalarProduct(normalVector);
        if (cosa > 0){
            cosa = -cosa;
        }
        else {
            float temp;
            temp = a;
            a = b;
            b = temp;
            n = n*-1;
        }
        float r = a/b;
        float k = 1 - r*r * (1 - cosa*cosa);
        return *this*r + n*(r*cosa - sqrt(k));

    }

    bool isZeroVector() {
        if (x == 0 && y == 0 && z == 0)
            return true;
        return false;
    }

    float length() {
        return sqrt(x*x + y*y + z*z);
    }

    void serialize(std::vector<char> *bytes){
        bytes->resize(serializedSize);
        char *ptr = bytes->data();
        memcpy(ptr, &x, sizeof(type)); ptr += sizeof(type);
        memcpy(ptr, &y,sizeof(type)); ptr += sizeof(type);
        memcpy(ptr, &z,sizeof(type)); ptr += sizeof(type);
    }

    void deserialize(const std::vector<char>& bytes) {
        const char* ptr = bytes.data();
        memcpy(&x, ptr, sizeof(type)); ptr += sizeof(type);
        memcpy(&y, ptr, sizeof(type)); ptr += sizeof(type);
        memcpy(&z, ptr, sizeof(type)); ptr += sizeof(type);
    }

    char getType(){
        return 'v';
    }

    void print() {
        std::cout << x << " " << y << " " << z << std::endl;
    }



};

#endif // VECTOR3_H
