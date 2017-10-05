#ifndef GLOBAL_H
#define GLOBAL_H

namespace myGlobals {

const float EPSILON = 0.0001f;

struct Chunk {
    int startx, stopx;
    int starty, stopy;
};

enum {
    EXIT,
    CAMERA,
    SCENE,
    CHUNK,
    PIXELS,
    DEPTH,
    NAME
};

enum {
    COINCIDENT,
    BACK,
    FRONT,
    SPANNING
};

}

#endif // GLOBAL_H
