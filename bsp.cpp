#include "bsp.h"

BSP::BSP()
{
    tree.front = nullptr;
    tree.back = nullptr;
    tree.polygons.clear();
}

void BSP::build()
{
    Scene::getInstance()->sceneObjects;
}
