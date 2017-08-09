#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>

template <typename type>
class Vector3
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
    type l;

    Vector3 operator +(const Vector3& v)
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator -(const Vector3& v)
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator *(const float& v) {
        return Vector3(v*x, v*y, v*z);
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
        return Vector3(y*v.z -  z*v.y, x*v.z - z*v.x, x*v.y - y*v.x);
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

    Vector3<float> reflect(Vector3 &n) {
        float n_dot_l = this->scalarProduct(n);
//        return n*(2*n_dot_l) - *this;
        return *this - n*(2*n_dot_l);
    }

};

#endif // VECTOR3_H
