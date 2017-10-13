#include "bsp.h"

BSP::BSP()
{
    tree.front = nullptr;
    tree.back = nullptr;
    Scene* scene = Scene::getInstance();

    for (int i = 0; i < scene->getNumOfObjects(); i++)
    {
        tree.polygons.push_back(static_cast<Triangle*>(scene->sceneObjects[i]));
    }

}

BSP::BSP(std::list<Triangle *> polygons) {

    tree.front = nullptr;
    tree.back = nullptr;
    tree.polygons = polygons;
}

BSP::~BSP()
{
    delete tree.back;
    delete tree.front;
}

void BSP::build(node *root, std::list<Triangle*> polygons, int depth)
{

    if (depth == 0){
        root->polygons = polygons;
        root->back = nullptr;
        root->front = nullptr;
        return;
    }

    depth --;
    int size = polygons.size();
    int result;
    Triangle* triangle;
    std::list<Triangle*> frontList, backList;
    root->partitionPlane = getBestPlane(polygons);
    while(!polygons.empty()) {

        triangle = polygons.back();
        polygons.pop_back();

        result = root->partitionPlane.classifyObject(triangle);

        switch (result) {
        case FRONT:
            frontList.push_back(triangle);
            break;

        case BACK:
            backList.push_back(triangle);
            break;

        case COINCIDENT:
            if (backList.size() < frontList.size()) {
                backList.push_back(triangle);
            }
            else {
                frontList.push_back(triangle);
            }
            break;

        case SPANNING: {
            std::list<Triangle*> tempFrontList, tempBackList;
            triangle->split(root->partitionPlane, tempFrontList, tempBackList);
            while (!tempBackList.empty()) {
                backList.push_back(tempBackList.back());
                tempBackList.pop_back();
            }
            while (!tempFrontList.empty()) {
                frontList.push_back(tempFrontList.back());
                tempFrontList.pop_back();
            }
        }
            break;


        default:
            break;
        }
    }

    if (frontList.size() > 1 && frontList.size() != size) {
    root->front = new node;
    build(root, frontList, depth);
    }
    else {
        root->front = new node;
        root->front->polygons = frontList;
        root->front->back = nullptr;
        root->front->front = nullptr;
    }

    if (backList.size() > 1 && backList.size() != size) {
        root->back = new node;
        build(root, backList, depth);
    }
    else {
        root->back = new node;
        root->back->polygons = backList;
        root->back->back = nullptr;
        root->back->front = nullptr;
    }

}

Plane BSP::getBestPlane(std::list<Triangle *> polygons)
{

    int front;
    int back;
    int spanning;

    int temp;
    int best = INT_MAX;
    Plane bestPlane;


    for (std::list<Triangle *>::iterator propTriangle = polygons.begin(); propTriangle != polygons.end(); ++propTriangle) {
        std::list<Plane> planes = (*propTriangle)->getPlanes();
        for (std::list<Plane>::iterator plane = planes.begin(); plane != planes.end(); ++plane) {
            front = 0;
            back = 0;
            spanning = 0;
            for (std::list<Triangle *>::iterator triangle = polygons.begin(); triangle != polygons.end(); ++triangle) {

                switch(plane->classifyObject(*triangle)) {

                case FRONT:
                    front++;
                    break;

                case BACK:
                    back++;
                    break;

                case COINCIDENT:
                    if (back < front) {
                        back++;
                    }
                    else {
                        front++;
                    }

                case SPANNING:
                    spanning++;
                    break;

                default:
                    break;

                }
             }

        //cost - SAH (equal num of triangles on both sides)
        temp = abs(front - back);
        temp += spanning;

        if (temp < best) {
            best = temp;
            bestPlane = *plane;
        }
    }}

    return bestPlane;
}

SceneObject *BSP::getClosest(Vector3<float> &crossPoint, Vector3<float> &startingPoint, Vector3<float> &directionVector)
{
    return intersect(&tree, crossPoint, startingPoint, directionVector);
}

SceneObject *BSP::intersect(BSP::node *root, Vector3<float> &crossPoint, Vector3<float> &startingPoint, Vector3<float> &directionVector)
{
    if (root->back == nullptr && root->front == nullptr) {
        //get closest from root's list
    }

    node *near;
    node *far;

    switch (root->partitionPlane.classifyPoint(&startingPoint)) {
    case FRONT:
            near = root->front;
            far = root->back;
        break;

    case BACK:
            near = root->back;
            far = root->front;
        break;

            //co jezeli wektor kierunkowy tez jest rownolegly z plaszczyzna?
    case COINCIDENT: {
            Vector3<float> point = startingPoint + directionVector;
            if (root->partitionPlane.classifyPoint(&point) == FRONT) {
                near = root->front;
                far = root->back;
            }
            else {
                near = root->back;
                far = root->front;
            }
        }
        break;

    default:
        return nullptr;
        break;
    }

    SceneObject* hit = intersect(near, crossPoint, startingPoint, directionVector);

    Vector3<float> normal = root->partitionPlane.getNormal();
    if (hit == nullptr && directionVector.scalarProduct(normal) <= EPSILON) {
        hit = intersect(far, crossPoint, startingPoint, directionVector);
    }

    return hit;

}

SceneObject *BSP::getClosestInNode(std::list<Triangle *> polygons, Vector3<float> &crossPoint, Vector3<float> &startingPoint, Vector3<float> &directionVector)
{

    Vector3<float> tempCrossPoint;
    float distance, tempDistance;
    Triangle* triangle = nullptr;

    for (std::list<Triangle *>::iterator it = polygons.begin(); it != polygons.end(); ++it) {

        if ((*it)->trace(tempCrossPoint, startingPoint, directionVector, tempDistance)) {
            if (triangle == nullptr) {
                triangle = *it;
                distance = tempDistance;
                crossPoint = tempCrossPoint;
            }
            else {
                if (tempDistance < distance) {
                    distance = tempDistance;
                    triangle = *it;
                    crossPoint = tempCrossPoint;
                }
            }

        }
    }

    return triangle;
}






