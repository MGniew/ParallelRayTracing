#ifndef MASTERMPI_H
#define MASTERMPI_H
#include "global.h"

#include "global.h"
#include "queue"
#include "vector"
#include "camera.h"


class MasterMPI
{
public:
    MasterMPI();
    void splitToChunks(int num);
    std::queue<Chunk> queue;
};

#endif // MASTERMPI_H
