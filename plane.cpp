#include "plane.h"

Plane::Plane()
{
    a=0;
    b=0;
    c=0;
    d=0;
}

Plane::Plane(float a, float b, float c, float d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

int Plane::classifyObject(SceneObject *obj)
{

    int pos = 0;
    int neg = 0;

    if (obj->getType() == 't') {


        Triangle* triangle = static_cast<Triangle*>(obj);
        Vector3<float>* point;


        for(int i=1; i<=3; i++) {
            point = triangle->getPointbyNum(i);

            switch (classifyPoint(point)) {
                case FRONT:
                    pos++;
                    break;
                case BACK:
                    neg++;
                    break;
                default:
                    break;
            }
        }

        if (pos > 0 && neg > 0)
                return SPANNING;

        if (pos > 0)
                return FRONT;

        if (neg > 0)
                return BACK;

        return COINCIDENT;

    }

    return -1;
}

int Plane::classifyPoint(Vector3<float> *point)
{
    float dist = getDistToPoint(point);

    if (dist > EPSILON)
        return FRONT;
    else
        if(dist < -EPSILON)
            return BACK;

    return COINCIDENT;
}

float Plane::getDistToPoint(Vector3<float> *point)
{
    float sqr = sqrt(a*a + b*b + c*c);
    float dist;
    dist = a*point->x + b*point->y + c*point->z + d;
    dist/=sqr;
    return dist;
}

bool Plane::rayIntersectPlane(Vector3<float> startingPoint, Vector3<float> directionVector)
{

    Vector3<float> normal = getNormal();
    directionVector.normalize();

    float denom = normal.scalarProduct(directionVector);
    if (fabs(denom) >= EPSILON){
    float t = (-(d + normal.scalarProduct(startingPoint))/denom);
        return (t >= 0);
    }
    return false;
}

Vector3<float> Plane::getNormal()
{
    Vector3<float> normal(a,b,c);
    //normal.normalize();
    return normal;
}

void Plane::print()
{
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Plane:" << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "d: " << d << std::endl;
    std::cout << "-------------------------------" << std::endl;

}
