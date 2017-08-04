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

};

#endif // VECTOR3_H