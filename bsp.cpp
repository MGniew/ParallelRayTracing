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

void BSP::build(node *root, std::list<Triangle*> polygons)
{
    if (root->polygons.size() == 1) return;
    int result;
    Triangle* triangle;
    std::list<Triangle*> frontList, backList;
    root->partitionPlane = getBestPlane(polygons);

    while(!polygons.empty()) {

        triangle = polygons.back();
        polygons.pop_front();

        result = root->partitionPlane.classifyObject(triangle);

        switch (result) {
        case FRONT:
        case COINCIDENT:
            frontList.push_back(triangle);
            break;

        case BACK:
            backList.push_back(triangle);
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

    tree.front = new node;
    build(tree.front, frontList);
    tree.back = new node;
    build(tree.back, backList);
}

//WHAT IS THE BEST PLANE?
Plane BSP::getBestPlane(std::list<Triangle *> polygons)
{

    int front; //if on front or coincident
    int back;
    int spanning;

    int temp;
    int best = INT_MAX;
    Plane bestPlane;


    for (std::list<Triangle *>::iterator propTriangle = polygons.begin(); propTriangle != polygons.end(); ++propTriangle) {

        front = 0;
        back = 0;
        spanning = 0;

        Plane plane = (*propTriangle)->getPlane();
        for (std::list<Triangle *>::iterator triangle = polygons.begin(); triangle != polygons.end(); ++triangle) {

            switch(plane.classifyObject(*triangle)) {

            case FRONT:
            case COINCIDENT:
                front++;
                break;

            case BACK:
                back++;
                break;

            case SPANNING:
                spanning++;
                break;

            default:
                break;

            }
        }

        //cost - SAH (equal num of triangles on both sides)
        //min fun
        //every spanning (in worst case) increase the difference by 1
        temp = abs(front - back);
        temp += spanning;

        if (temp < best) {
            best = temp;
            bestPlane = plane;
        }
    }

    return bestPlane;
}


