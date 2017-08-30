#include "light.h"

Light::Light()
{
    pos = new Vector3<float>(0.0, 3.0, -3.0);
    amb = new Vector3<float>(0.1, 0.1, 0.1);
    dif = new Vector3<float>(0.7, 0.8, 0.61);
    spec = new Vector3<float>(0.9, 0.8, 0.8);

    serializedSize = 4 * Vector3<float>::serializedSize;
}

Light::Light(Vector3<float>* pos, Vector3<float>* amb, Vector3<float>* dif, Vector3<float>* spec)
{
    this->pos = pos;
    this->amb = amb;
    this->dif = dif;
    this->spec = spec;

    serializedSize = 4 * Vector3<float>::serializedSize;
}

Light::~Light()
{
    delete pos;
    delete amb;
    delete dif;
    delete spec;
}

void Light::setPos(float x, float y, float z)
{
    pos->x = x;
    pos->y = y;
    pos->z = z;
}

void Light::setAmb(float r, float g, float b)
{
    amb->x = r;
    amb->y = g;
    amb->z = b;
}

void Light::setDif(float r, float g, float b)
{
    dif->x = r;
    dif->y = g;
    dif->z = b;
}

void Light::setSpec(float r, float g, float b)
{
    spec->x = r;
    spec->y = g;
    spec->z = b;
}

void Light::serialize(std::vector<char> *bytes)
{
    bytes->resize(serializedSize);
    char *ptr = bytes->data();
    std::vector<char> vec;
    pos->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += sizeof(vec.size());
    amb->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += sizeof(vec.size());
    dif->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += sizeof(vec.size());
    spec->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size());
}

void Light::deserialize(const std::vector<char> &bytes)
{
    const char* ptr = bytes.data();
    std::vector<char> vec;
    vec.resize(Vector3<float>::serializedSize);
    memcpy(vec.data(), ptr, vec.size()); ptr += sizeof(vec.size());
    pos->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += sizeof(vec.size());
    amb->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += sizeof(vec.size());
    dif->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size());
    spec->deserialize(vec);

}

char Light::getType()
{
    return 'l';
}

Vector3<float>* Light::getSpec()
{
    return spec;
}

Vector3<float>* Light::getDif()
{
    return dif;
}

Vector3<float>* Light::getAmb()
{
    return amb;
}

Vector3<float>* Light::getPos()
{
    return pos;
}
