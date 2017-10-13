#include "triangle.h"
#include "plane.h"

Triangle::Triangle(Vector3<float> *pointA,
                   Vector3<float> *pointB,
                   Vector3<float> *pointC,
                   Vector3<float> *normalA,
                   Vector3<float> *normalB,
                   Vector3<float> *normalC,
                   float texCoordsX, float texCoordsY,
                   Vector3<float>* amb,
                   Vector3<float>* dif,
                   Vector3<float>* spec,
                   float specShin,
                   float transparency,
                   float mirror,
                   float local,
                   float density) : SceneObject(amb, dif, spec, specShin, transparency, mirror, local, density)
{
    this->pointA = pointA;
    this->pointB = pointB;
    this->pointC = pointC;

    Vector3<float> ab = *pointB - *pointA;
    Vector3<float> ac = *pointC - *pointA;
    Vector3<float> normal = ab.vectorProduct(ac).normalize();

    if (normalA != nullptr)
        this->normalA = normalA;
    else
        this->normalA = new Vector3<float>(normal.x, normal.y, normal.z);

    if (normalB != nullptr)
        this->normalB = normalB;
    else
        this->normalB = new Vector3<float>(normal.x, normal.y, normal.z);

    if (normalC != nullptr)
        this->normalC = normalC;
    else
        this->normalC = new Vector3<float>(normal.x, normal.y, normal.z);

    this->texCoordsX = texCoordsX;
    this->texCoordsY = texCoordsY;

    serializedSize = 9 * Vector3<float>::serializedSize +
                     7 * sizeof(float);
}

Triangle::~Triangle()
{
    delete pointA;
    delete pointB;
    delete pointC;
    delete normalA;
    delete normalB;
    delete normalC;
}

Triangle::Triangle()
{
    pointA = new Vector3<float>;
    pointB = new Vector3<float>;
    pointC = new Vector3<float>;
    normalA = new Vector3<float>;
    normalB = new Vector3<float>;
    normalC = new Vector3<float>;
    amb = new Vector3<float>;
    dif = new Vector3<float>;
    spec = new Vector3<float>;

    serializedSize = 9 * Vector3<float>::serializedSize +
            7 * sizeof(float);
}

Triangle::Triangle(Triangle &triangle) : SceneObject(triangle.getAmb(),
                                                     triangle.getDif(),
                                                     triangle.getSpec(),
                                                     triangle.getSpecShin(),
                                                     triangle.getTransparency(),
                                                     triangle.getMirror(),
                                                     triangle.getLocal(),
                                                     triangle.getDensity())
{
    pointA = new Vector3<float>(*triangle.pointA);
    pointB = new Vector3<float>(*triangle.pointB);
    pointC = new Vector3<float>(*triangle.pointC);
    normalA = new Vector3<float>(*triangle.normalA);
    normalB = new Vector3<float>(*triangle.normalB);
    normalC = new Vector3<float>(*triangle.normalC);
    texCoordsX = triangle.texCoordsX;
    texCoordsY = triangle.texCoordsY;

    serializedSize = 9 * Vector3<float>::serializedSize +
            7 * sizeof(float);
}

//Möller–Trumbore intersection algorithm
bool Triangle::trace(Vector3<float>& crossPoint, Vector3<float>& startPoint, Vector3<float>& directionVector, float& dist) {

    Vector3<float> v0v1 = *pointB - *pointA;
    Vector3<float> v0v2 = *pointC - *pointA;
    Vector3<float> pvec =  directionVector.vectorProduct(v0v2);
    float u,v;

    float det = v0v1.scalarProduct(pvec);

    if(det<EPSILON && det>-EPSILON) return false;

    float invDet = 1.0f / det;

    Vector3<float> tvec = startPoint - *pointA;
    u = tvec.scalarProduct(pvec) * invDet;
    if (u < 0 || u > 1) return false;

    Vector3<float> qvec = tvec.vectorProduct(v0v1);
    v = directionVector.scalarProduct(qvec) * invDet;
    if (v < 0 || u + v > 1) return false;

    dist = v0v2.scalarProduct(qvec) * invDet;

    if ((dist) > EPSILON){
        crossPoint = startPoint + directionVector*dist;
        return true;
    }
    return false;
}

//classical math
//bool Triangle::trace(Vector3<float>& crossPoint, Vector3<float>& startPoint, Vector3<float>& directionVector) {
//    Vector3<float> ab = *pointB - *pointA;
//    Vector3<float> ac = *pointC - *pointA;
//    Vector3<float> normal = ab.vectorProduct(ac);
//    normal.normalize();

//    //step1: find crosspoint with plane
//    float NdotRayDirection = normal.scalarProduct(directionVector);

//    float d = normal.scalarProduct(*pointA);
//    t = (d - normal.scalarProduct(startPoint))/NdotRayDirection;

//    crossPoint = startPoint + directionVector*t;

//    return true;
//    Vector3<float> ab = *pointB - *pointA;
//    Vector3<float> ac = *pointC - *pointA;
//    Vector3<float> normal = ab.vectorProduct(ac);
//    normal.normalize();

//    //step1: find crosspoint with plane
//    float NdotRayDirection = normal.scalarProduct(directionVector);
//    if (fabs(NdotRayDirection) < 0.000001) // almost 0 (also in sphere change that!)
//        return false;
//    float d = normal.scalarProduct(*pointA);
//    float t = (d - normal.scalarProduct(startPoint))/NdotRayDirection;
//    // check if the triangle is in behind the ray
//    if (t < 0) return false; // the triangle is behind

//    crossPoint = startPoint + directionVector*t;
//    // Step 2: inside-outside test
//    Vector3<float> C; // vector perpendicular to triangle's plane

//    Vector3<float> edge0 = *pointB - *pointA;
//    Vector3<float> vp0 = crossPoint - *pointA;
//    C = edge0.vectorProduct(vp0);
//    if (normal.scalarProduct(C) < 0) return false; // P is on the right sid

//    Vector3<float> edge1 = *pointC - *pointB;
//    Vector3<float> vp1 = crossPoint - *pointB;
//    C = edge1.vectorProduct(vp1);
//    if (normal.scalarProduct(C) < 0) return false; // P is on the right side

//    Vector3<float> edge2 = *pointA - *pointC;
//    Vector3<float> vp2 = crossPoint - *pointC;
//    C = edge2.vectorProduct(vp2);
//    if (normal.scalarProduct(C) < 0) return false; // P is on the right side;

//    return true;

//}

Vector3<float> Triangle::getNormalVector(Vector3<float>& crossPoint) {

    //consider cache those
    Vector3<float> ab = *pointA - *pointB;
    Vector3<float> bc = *pointB - *pointC;
    Vector3<float> ca = *pointC - *pointA;

    Vector3<float> ap = *pointA - crossPoint;
    Vector3<float> bp = *pointB - crossPoint;

    float abArea = Area(ab, ap);
    float bcArea = Area(bc, bp);
    float caArea = Area(ca, ap);

    //division by total area is not nessesery since i must normalize result anyway
    Vector3<float> result = (*normalA*bcArea + *normalB*caArea + *normalC*abArea);
    result.normalize();
    return result;
}

void Triangle::print()
{
    std::cout << "Triangle: " << std::endl;
    std::cout << "normalA"; normalA->print();
    std::cout << "normalB: "; normalB->print();
    std::cout << "normalC: "; normalC->print();
    std::cout << "pointA: "; pointA->print();
    std::cout << "pointB: "; pointB->print();
    std::cout << "pointC: "; pointC->print();
    std::cout << "amb: "; amb->print();
    std::cout << "dif: "; dif->print();
    std::cout << "spec: "; spec->print();

    std::cout << "texCoordsX: " << texCoordsX << std::endl;
    std::cout << "texCoordsY: " << texCoordsY << std::endl;
    std::cout << "mirror: " << mirror << std::endl;
    std::cout << "transparency: " << transparency << std::endl;
    std::cout << "local: "  << local << std::endl;
    std::cout << "specShin: " << specShin << std::endl;
    std::cout << "density: " << density << std::endl;
    std::cout << "--------------------------------------" << std::endl;

}

float Triangle::Area(Vector3<float> a, Vector3<float> b)
{
    return a.vectorProduct(b).length()/2;
}

Plane Triangle::getPlane()
{
    Vector3<float> v0v1 = *pointB - *pointA;
    Vector3<float> v0v2 = *pointC - *pointA;
    Vector3<float> normal = v0v1.vectorProduct(v0v2);

    float d = normal.x * -pointA->x + normal.y * -pointA->y + normal.z * -pointA->z;

    return Plane(normal.x, normal.y, normal.z, d);
}

Plane Triangle::getPerpendicularPlane(int i)
{
    if (i < 1 || i > 3) return Plane();

    Vector3<float> v0v1 = *pointB - *pointA;
    Vector3<float> v0v2 = *pointC - *pointA;
    Vector3<float> normalTriangle = v0v1.vectorProduct(v0v2);

    Vector3<float> edge;
    Vector3<float>* point;

    switch(i) {
        case 1:
            edge = *pointB - *pointA;
            point = pointA;
            break;
        case 2:
            edge = *pointC - *pointA;
            point = pointA;
            break;
        case 3:
            edge = *pointC - *pointB;
            point = pointB;
            break;

        default:
            return Plane();
    }
    Vector3<float> normal = normalTriangle.vectorProduct(edge);
    float d = normal.x * -point->x + normal.y * -point->y + normal.z * -point->z;
    return Plane(normal.x, normal.y, normal.z, d);


}

std::list<Plane> Triangle::getPlanes()
{
    std::list<Plane> list;

    list.push_back(getPlane());
    for (int i = 1; i < 4; i++) {
        Plane plane = getPerpendicularPlane(i);
        list.push_back(plane);

    }
    return list;
}

Vector3<float>* Triangle::getPointbyNum(int a)
{
    switch (a) {
    case 1:
        return pointA;
        break;
    case 2:
        return pointB;
        break;
    case 3:
        return pointC;
        break;
    default:
        return nullptr;
        break;
    }
}

void Triangle::split(Plane plane, std::list<Triangle*>& front, std::list<Triangle*>& back)
{
    std::vector<Vector3<float>> frontSide;
    std::vector<Vector3<float>> backSide;


    Vector3<float> *pointA, *pointB;
    float distA, distB;

    pointA = getPointbyNum(3);
    distA = plane.getDistToPoint(pointA);


    //should work 4 every poligon
    for (int i=1; i<=3; i++) {
        pointB = getPointbyNum(i);
        distB = plane.getDistToPoint(pointB);

        if (distB > 0) {
            if (distA < 0) { //different sides

                Vector3<float> v = *pointB - *pointA;
                float distToSpan = -plane.getDistToPoint(pointA)/ (plane.getNormal().scalarProduct(v));
                Vector3<float> newPoint = *pointA + (v*distToSpan);
                frontSide.push_back(newPoint);
                backSide.push_back(newPoint);
            }
                frontSide.push_back(*pointB);
        }
        else if (distB < 0) {
            if (distA > 0) //different sides
            {
                Vector3<float> v = *pointB - *pointA;
                float distToSpan = -plane.getDistToPoint(pointA)/ (plane.getNormal().scalarProduct(v));
                Vector3<float> newPoint = *pointA + v*distToSpan;
                frontSide.push_back(newPoint);
                backSide.push_back(newPoint);
            }
                backSide.push_back(*pointB);
        }
        else {
            frontSide.push_back(*pointB);
            backSide.push_back(*pointB);
        }
            pointA = pointB;
            distA = distB;
    }

    //works only for triangle (4 side polygon to 3 side polygon
    if (frontSide.size() == 3) {
        Triangle* triangle = new Triangle(*this);
        triangle->pointA->setValues(frontSide[0]);
        triangle->pointB->setValues(frontSide[1]);
        triangle->pointC->setValues(frontSide[2]);
        triangle->normalA->setValues(getNormalVector(frontSide[0]));
        triangle->normalB->setValues(getNormalVector(frontSide[1]));
        triangle->normalC->setValues(getNormalVector(frontSide[2]));
        front.push_back(triangle);
        Scene::getInstance()->addObject(front.back());
    }
    else {


        Triangle* triangle = new Triangle(*this);
        triangle->pointA->setValues(frontSide[0]);
        triangle->pointB->setValues(frontSide[1]);
        triangle->pointC->setValues(frontSide[2]);
        triangle->normalA->setValues(getNormalVector(frontSide[0]));
        triangle->normalB->setValues(getNormalVector(frontSide[1]));
        triangle->normalC->setValues(getNormalVector(frontSide[2]));
        front.push_back(triangle);
        Scene::getInstance()->addObject(front.back());

        triangle = new Triangle(*this);
        triangle->pointA->setValues(frontSide[0]);
        triangle->pointB->setValues(frontSide[2]);
        triangle->pointC->setValues(frontSide[3]);
        triangle->normalA->setValues(getNormalVector(frontSide[0]));
        triangle->normalB->setValues(getNormalVector(frontSide[2]));
        triangle->normalC->setValues(getNormalVector(frontSide[3]));
        front.push_back(triangle);
        Scene::getInstance()->addObject(front.back());
    }

    if (backSide.size() == 3) {

        Triangle* triangle = new Triangle(*this);
        triangle->pointA->setValues(backSide[0]);
        triangle->pointB->setValues(backSide[1]);
        triangle->pointC->setValues(backSide[2]);
        triangle->normalA->setValues(getNormalVector(backSide[0]));
        triangle->normalB->setValues(getNormalVector(backSide[1]));
        triangle->normalC->setValues(getNormalVector(backSide[2]));
        back.push_back(triangle);
        Scene::getInstance()->addObject(front.back());
    }
    else {

        Triangle* triangle = new Triangle(*this);
        triangle->pointA->setValues(backSide[0]);
        triangle->pointB->setValues(backSide[1]);
        triangle->pointC->setValues(backSide[2]);
        triangle->normalA->setValues(getNormalVector(backSide[0]));
        triangle->normalB->setValues(getNormalVector(backSide[1]));
        triangle->normalC->setValues(getNormalVector(backSide[2]));
        back.push_back(triangle);
        Scene::getInstance()->addObject(front.back());

        triangle = new Triangle(*this);
        triangle->pointA->setValues(backSide[0]);
        triangle->pointB->setValues(backSide[2]);
        triangle->pointC->setValues(backSide[3]);
        triangle->normalA->setValues(getNormalVector(backSide[0]));
        triangle->normalB->setValues(getNormalVector(backSide[2]));
        triangle->normalC->setValues(getNormalVector(backSide[3]));
        back.push_back(triangle);
        Scene::getInstance()->addObject(front.back());

    }

}

void Triangle::serialize(std::vector<char> *bytes)
{
    bytes->resize(serializedSize);
    char *ptr = bytes->data();
    std::vector<char> vec;

    pointA->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    pointB->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    pointC->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    normalA->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    normalB->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    normalC->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();

    memcpy(ptr, &texCoordsX, sizeof(texCoordsX)); ptr += sizeof(texCoordsX);
    memcpy(ptr, &texCoordsY, sizeof(texCoordsY)); ptr += sizeof(texCoordsY);

    amb->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    dif->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();
    spec->serialize(&vec);
    memcpy(ptr, vec.data(), vec.size()); ptr += vec.size();

    memcpy(ptr, &specShin, sizeof(specShin)); ptr += sizeof(specShin);
    memcpy(ptr, &transparency, sizeof(transparency)); ptr += sizeof(transparency);
    memcpy(ptr, &mirror, sizeof(mirror)); ptr += sizeof(mirror);
    memcpy(ptr, &local, sizeof(local)); ptr += sizeof(local);
    memcpy(ptr, &density, sizeof(density));
}

void Triangle::deserialize(const std::vector<char> &bytes)
{
    const char* ptr = bytes.data();
    std::vector<char> vec;
    vec.resize(Vector3<float>::serializedSize);

    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    pointA->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    pointB->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    pointC->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    normalA->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    normalB->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    normalC->deserialize(vec);

    memcpy(&texCoordsX, ptr, sizeof(texCoordsX)); ptr += sizeof(texCoordsX);
    memcpy(&texCoordsY, ptr, sizeof(texCoordsY)); ptr += sizeof(texCoordsY);

    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    amb->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    dif->deserialize(vec);
    memcpy(vec.data(), ptr, vec.size()); ptr += vec.size();
    spec->deserialize(vec);

    memcpy(&specShin, ptr, sizeof(specShin)); ptr += sizeof(specShin);
    memcpy(&transparency, ptr, sizeof(transparency)); ptr += sizeof(transparency);
    memcpy(&mirror, ptr, sizeof(mirror)); ptr += sizeof(mirror);
    memcpy(&local, ptr, sizeof(local)); ptr += sizeof(local);
    memcpy(&density, ptr, sizeof(density));
}

char Triangle::getType()
{
    return 't';
}
