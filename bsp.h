#ifndef BSP_H
#define BSP_H

#include "list"
#include "triangle.h"
#include "plane.h"
#include "limits.h"

class BSP
{
public:

    BSP();
    BSP(std::list<Triangle*> polygons) ;
    ~BSP();

    struct node {

        Plane partitionPlane;
        std::list<Triangle*> polygons;
        node* front;
        node* back;

    } ;

    node tree;

    void build(node *root, std::list<Triangle*> polygons, int depth);
    Plane getBestPlane(std::list<Triangle*> polygons);
    SceneObject *getClosest(Vector3<float> &crossPoint,
                            Vector3<float> &startingPoint,
                            Vector3<float> &directionVector);

private:

    SceneObject* intersect(node *root,
                           Vector3<float> &crossPoint,
                           Vector3<float> &startingPoint,
                           Vector3<float> &directionVector);

    SceneObject* getClosestInNode(std::list<Triangle*> polygons,
                                  Vector3<float> &crossPoint,
                                  Vector3<float> &startingPoint,
                                  Vector3<float> &directionVector);
};

#endif // BSP_H
