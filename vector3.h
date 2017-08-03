#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>

template <typename type>
class Vector3
{
public:
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
      return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
    }

    Vector3 operator -(const Vector3& v)
    {
     return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
    }

    void normalize()
    {
        float d = x*x + y*y + z*z;
        d = sqrt(d);
        x/=d;
        y/=d;
        z/=d;
    }

private:


};

#endif // VECTOR3_H
