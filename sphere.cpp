#include "sphere.h"

Sphere::Sphere(Vector3<float>* amb,
               Vector3<float>* dif,
               Vector3<float>* spec,
               float specShin,
               Vector3<float>* pos,
               float radius,
               float transparency,
               float mirror,
               float local,
               float density) : SceneObject(amb, dif, spec, specShin, transparency, mirror, local, density)
{
    this->pos = pos;
    this->radius = radius;

    serializedSize = 4 * Vector3<float>::serializedSize +
                     6 * sizeof(float);
}

Sphere::~Sphere()
{

}

Sphere::Sphere()
{
    amb = new Vector3<float>;
    dif = new Vector3<float>;
    spec = new Vector3<float>;
    pos = new Vector3<float>;

    serializedSize = 4 * Vector3<float>::serializedSize +
                   6 * sizeof(float);

}

bool Sphere::trace(Vector3<float>& crossPoint, Vector3<float>& startPoint, Vector3<float>& directionVector) {

     float a, b, c, d, r1, r2;
     float sqr;

     Vector3<float> distance = startPoint-*pos;
     a = directionVector.scalarProduct(directionVector);
     b = 2 * directionVector.scalarProduct(distance);
     c = distance.scalarProduct(distance) - radius*radius;

     d = b*b - 4*a*c;

     if (d<0) return false;
     sqr = sqrt(d);
         if (d>0) {
            r1 = (-b - sqr)/(2*a);
            r2 = (-b + sqr)/(2*a);
            if (r1 < 0 && r2 < 0) return false;
            if (r1 < 0)
                r1 = r2;
         } else
             r1 = (-b)/(2*a);

         crossPoint.x = startPoint.x + r1*directionVector.x;
         crossPoint.y = startPoint.y + r1*directionVector.y;
         crossPoint.z = startPoint.z + r1*directionVector.z;
         return true;

}

Vector3<float> Sphere::getNormalVector(Vector3<float>& crossPoint) {

    Vector3<float> normalVector = crossPoint - *pos;
    return normalVector.normalize();
}

void Sphere::print()
{
    std::cout << "Sphere" << std::endl;

    std::cout << "amb: "; amb->print();
    std::cout << "dif: "; dif->print();
    std::cout << "spec: "; spec->print();
    std::cout << "pos: "; pos->print();


     std::cout << "radius: " << radius << std::endl;
    std::cout << "mirror: " << mirror << std::endl;
    std::cout << "transparency: " << transparency << std::endl;
    std::cout << "local: "  << local << std::endl;
    std::cout << "specShin: " << specShin << std::endl;
    std::cout << "density: " << density << std::endl;
    std::cout << "=--------------------------------------" << std::endl;
}

void Sphere::serialize(std::vector<char> *bytes)
{
    bytes->resize(serializedSize);
    char *ptr = bytes->data();
    std::vector<char> vec;

    amb->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    dif->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    spec->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();

    memcpy(ptr, &specShin, sizeof(specShin)); ptr += sizeof(specShin);

    pos->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();

    memcpy(ptr, &radius, sizeof(radius)); ptr += sizeof(radius);
    memcpy(ptr, &transparency, sizeof(transparency)); ptr += sizeof(transparency);
    memcpy(ptr, &mirror, sizeof(mirror)); ptr += sizeof(mirror);
    memcpy(ptr, &local, sizeof(local)); ptr += sizeof(local);
    memcpy(ptr, &density, sizeof(density));
}

void Sphere::deserialize(const std::vector<char> &bytes)
{
    const char* ptr = bytes.data();
    std::vector<char> vec;
    vec.resize(Vector3<float>::serializedSize);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    amb->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    dif->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    spec->deserialize(vec);

    memcpy(&specShin, ptr, sizeof(specShin)); ptr += sizeof(specShin);

    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    pos->deserialize(vec);

    memcpy(&radius, ptr, sizeof(radius)); ptr += sizeof(radius);
    memcpy(&transparency, ptr, sizeof(transparency)); ptr += sizeof(transparency);
    memcpy(&mirror, ptr, sizeof(mirror)); ptr += sizeof(mirror);
    memcpy(&local, ptr, sizeof(local)); ptr += sizeof(local);
    memcpy(&density, ptr, sizeof(density));
}

char Sphere::getType()
{
    return 's';
}
