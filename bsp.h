#ifndef BSP_H
#define BSP_H

#include "list"
#include "sceneobject.h".h"
#include "plane.h"
#include "limits.h"

class BSP
{
public:

    BSP();
    BSP(std::list<SceneObject*> polygons) ;
    ~BSP();

    struct node {

        Plane partitionPlane;
        std::list<SceneObject*> polygons;
        node* front;
        node* back;

    } ;

    node *tree;
    std::list<SceneObject*> polygons;

    void build(node *root, std::list<SceneObject*> polygons, int depth);
    Plane getBestPlane(std::list<SceneObject*> polygons);
    SceneObject *getClosest(Vector3<float> &crossPoint,
                            Vector3<float> &startingPoint,
                            Vector3<float> &directionVector);

    bool isInShadow(Vector3<float> &crossPoint,
                    Vector3<float> &directionVector,
                    Vector3<float> &lightPos);

private:

    SceneObject* intersect(node *root,
                           Vector3<float> &crossPoint,
                           Vector3<float> &startingPoint,
                           Vector3<float> &directionVector);

    void getTmp(node *root,
                std::list<SceneObject*> &list);

    SceneObject* getClosestInNode(std::list<SceneObject*> polygons,
                                  Vector3<float> &crossPoint,
                                  Vector3<float> &startingPoint,
                                  Vector3<float> &directionVector);

    bool isInShadow_tree(node *root,
                         Vector3<float> &crossPoint,
                         Vector3<float> &directionVector,
                         float LightDistance);


    void deleteTree(node *root);

};

#endif // BSP_H
