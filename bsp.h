#ifndef BSP_H
#define BSP_H

#include "list"
#include "triangle.h"
#include "plane.h"

class BSP
{
public:
    BSP();

    struct node {

        Plane partition;
        std::list<Triangle> polygons;
        node* front;
        node* back;

    };

    node tree;

    void build();
};

#endif // BSP_H
