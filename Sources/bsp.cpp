#include "bsp.h"

BSP::BSP()
{
    tree = new node;
    tree->front = nullptr;
    tree->back = nullptr;
    Scene* scene = Scene::getInstance();
    scene->setBSPUsage(false);
    for (int i = 0; i < scene->getNumOfObjects(); i++)
    {
        polygons.push_back(scene->sceneObjects[i]);

    }
    tree->polygons.empty();

    boundingBox = getBoundingBox(polygons);

}

BSP::BSP(std::list<SceneObject *> polygons) {

    tree = new node;
    tree->front = nullptr;
    tree->back = nullptr;
    this->polygons = polygons;
    boundingBox = getBoundingBox(polygons);
    tree->polygons.empty();
}

BSP::~BSP()
{
   deleteTree(tree);
}


void BSP::deleteTree(BSP::node *root)
{
    if (root != nullptr) {
        deleteTree(root->front);
        deleteTree(root->back);
        delete root;
    }
}

void BSP::build(node *root, std::list<SceneObject*> polygons, int depth)
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
    SceneObject* object;
    std::list<SceneObject*> frontList, backList;
    root->partitionPlane = getBestPlane(polygons);

    if (!root->partitionPlane.isValid()) {
        root->polygons = polygons;
        root->back = nullptr;
        root->front = nullptr;
        return;
    }

    while(!polygons.empty()) {

        object = polygons.back();
        polygons.pop_back();

        result = root->partitionPlane.classifyObject(object);
        switch (result) {
        case FRONT:
            frontList.push_back(object);
        break;

        case BACK:
            backList.push_back(object);
        break;

        case COINCIDENT:
            backList.push_back(object);
            frontList.push_back(object);

        break;

        case SPANNING: {
            if (object->getType() == 's') {
                root->polygons.push_back(object);
            } else {
                Triangle *triangle = static_cast<Triangle*>(object);
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
        }
        break;


        default:
        break;
        }
    }

    if (frontList.size() > 1 && frontList.size() != size) {
        root->front = new node;
        build(root->front, frontList, depth);
    }
    else {
        root->front = new node;
        root->front->polygons = frontList;
        root->front->back = nullptr;
        root->front->front = nullptr;
    }

    if (backList.size() > 1 && backList.size() != size) {
        root->back = new node;
        build(root->back, backList, depth);
    }
    else {
        root->back = new node;
        root->back->polygons = backList;
        root->back->back = nullptr;
        root->back->front = nullptr;
    }

}

Plane BSP::getBestPlane(std::list<SceneObject *> polygons)
{

    int front;
    int back;
    int spanning;

    int temp;
    int best = INT_MAX;
    Plane bestPlane;


    for (std::list<SceneObject *>::iterator propObj = polygons.begin(); propObj != polygons.end(); ++propObj) {
        if ((*propObj)->getType() != 't') continue;
        Triangle* triangle = static_cast<Triangle*>(*propObj);
        std::list<Plane> planes = triangle->getPlanes();
        for (std::list<Plane>::iterator plane = planes.begin(); plane != planes.end(); ++plane) {
            front = 0;
            back = 0;
            spanning = 0;
            for (std::list<SceneObject *>::iterator object = polygons.begin(); object != polygons.end(); ++object) {

                switch(plane->classifyObject(*object)) {

                case FRONT:
                    front++;
                    break;

                case BACK:
                    back++;
                    break;

                case COINCIDENT:
                    break;

                case SPANNING:
                    spanning++;
                    break;

                default:
                    break;

                }
             }

        temp = abs(front - back);
        temp += 2 * spanning;

        if (temp < best) {
            best = temp;
            bestPlane = *plane;
        }
    }}

    return bestPlane;
}

SceneObject *BSP::getClosest(Vector3<float> &crossPoint, Vector3<float> &startingPoint, Vector3<float> &directionVector)
{
    if (boundingBox.intersect(startingPoint, directionVector)) {
        return intersect(tree, crossPoint, startingPoint, directionVector);
    }
    return nullptr;
}

SceneObject *BSP::intersect(BSP::node *root, Vector3<float> &crossPoint, Vector3<float> &startingPoint, Vector3<float> &directionVector)
{

    if (root->back == nullptr && root->front == nullptr) {
        return getClosestInNode(root->polygons, crossPoint, startingPoint, directionVector);
    }

    SceneObject *thisNodeHit = nullptr;
    Vector3<float> tempCross;

    if(!root->polygons.empty()) {
        thisNodeHit = getClosestInNode(root->polygons, tempCross, startingPoint, directionVector);
    }

    node *near;
    node *far;
    SceneObject *hit = nullptr;;


    switch (root->partitionPlane.classifyPoint(&startingPoint)) {
    case FRONT:
            near = root->front;
            far = root->back;
        break;

    case BACK:
            near = root->back;
            far = root->front;
        break;

    case COINCIDENT: {

            if (root->partitionPlane.getNormal().scalarProduct(directionVector) >= 0) {
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

    hit = intersect(near, crossPoint, startingPoint, directionVector);

    if (hit == nullptr && root->partitionPlane.rayIntersectPlane(startingPoint,directionVector)) {
        hit = intersect(far, crossPoint, startingPoint, directionVector);
    }

    if (thisNodeHit != nullptr) {
        if (hit != nullptr) {
            if (tempCross.distanceFrom(startingPoint) < crossPoint.distanceFrom(startingPoint)) {
                hit = thisNodeHit;
                crossPoint = tempCross;
            }
        }
        else {
            hit = thisNodeHit;
            crossPoint = tempCross;
        }
    }


    return hit;

}

void BSP::getTmp(BSP::node *root, std::list<SceneObject *> &list)
{
    if (root->back==nullptr && root->front == nullptr) {
        list.insert(list.end(), root->polygons.begin(), root->polygons.end());
        return;
    }
    getTmp(root->back, list);
    getTmp(root->front, list);
}

SceneObject *BSP::getClosestInNode(std::list<SceneObject *> polygons, Vector3<float> &crossPoint, Vector3<float> &startingPoint, Vector3<float> &directionVector)
{

    Vector3<float> tempCrossPoint;
    float distance, tempDistance;
    SceneObject* object = nullptr;

    for (std::list<SceneObject *>::iterator it = polygons.begin(); it != polygons.end(); ++it) {

        if ((*it)->trace(tempCrossPoint, startingPoint, directionVector, tempDistance)) {
            if (object == nullptr) {
                object = *it;
                distance = tempDistance;
                crossPoint = tempCrossPoint;
            }
            else {
                if (tempDistance < distance) {
                    distance = tempDistance;
                    object = *it;
                    crossPoint = tempCrossPoint;
                }
            }

        }
    }

    return object;
}


bool BSP::isInShadow(Vector3<float> &crossPoint, Vector3<float> &directionVector, Vector3<float> &lightPos)
{
    return isInShadow_tree(tree, crossPoint, directionVector, crossPoint.distanceFrom(lightPos));
}

BoundingBox BSP::getBoundingBox(std::list<SceneObject *> polygons)
{
    BoundingBox box;

    box.maxX = polygons.back()->getBoundingBox().maxX;
    box.minX = polygons.back()->getBoundingBox().minX;
    box.maxY = polygons.back()->getBoundingBox().maxY;
    box.minY = polygons.back()->getBoundingBox().minY;
    box.maxZ = polygons.back()->getBoundingBox().maxZ;
    box.minZ = polygons.back()->getBoundingBox().minZ;

    BoundingBox objectBox;



    for (std::list<SceneObject *>::iterator it = polygons.begin(); it != polygons.end(); ++it) {

        objectBox = (*it)->getBoundingBox();

        if (objectBox.maxX > box.maxX) {
            box.maxX = objectBox.maxX;
        }

        if (objectBox.minX < box.minX) {
            box.minX = objectBox.minX;
        }

        if (objectBox.maxY > box.maxY) {
            box.maxY = objectBox.maxY;
        }

        if (objectBox.minY < box.minY) {
            box.minY = objectBox.minY;
        }

        if (objectBox.maxZ > box.maxZ) {
            box.maxZ = objectBox.maxZ;
        }

        if (objectBox.minZ < box.minZ) {
            box.minZ = objectBox.minZ;
        }
    }

    return box;
}

bool BSP::isInShadow_tree(BSP::node *root, Vector3<float> &crossPoint, Vector3<float> &directionVector, float lightDistance)
{
    Vector3<float> tempCrossPoint;
    float dist;

    if ((root->back == nullptr && root->front == nullptr) || !root->polygons.empty()) {
         for (std::list<SceneObject *>::iterator it = root->polygons.begin(); it != root->polygons.end(); ++it) {
             if ((*it)->trace(tempCrossPoint, crossPoint, directionVector, dist)) {
                if (dist < lightDistance) {
                    return true;
                }
             }
         }
    }

    if (root->back == nullptr && root->front == nullptr) {
        return false;
    }

    node *near;
    node *far;
    bool hit = false;

    switch (root->partitionPlane.classifyPoint(&crossPoint)) {
    case FRONT:
            near = root->front;
            far = root->back;
        break;

    case BACK:
            near = root->back;
            far = root->front;
        break;

    case COINCIDENT: {

            Vector3<float> point = crossPoint + directionVector;
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
        return false;
        break;
    }

    hit = isInShadow_tree(near, crossPoint, directionVector, lightDistance);

    if (hit == false && root->partitionPlane.rayIntersectPlane(crossPoint,directionVector)) {
        hit = isInShadow_tree(far, crossPoint, directionVector, lightDistance);
    }
    return hit;
}
