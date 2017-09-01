#ifndef GLOBAL_H
#define GLOBAL_H

namespace myGlobals {

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
    DEPTH
};

}

#endif // GLOBAL_H
