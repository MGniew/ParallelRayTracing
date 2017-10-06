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

    void build(node *root, std::list<Triangle*> polygons);
    Plane getBestPlane(std::list<Triangle*> polygons);
};

#endif // BSP_H
