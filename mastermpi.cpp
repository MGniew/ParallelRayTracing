#include "mastermpi.h"

MasterMPI::MasterMPI()
{

}


//split image to chunks and add them to queue
void MasterMPI::splitToChunks(int num) {
    Camera* camera = Camera::getInstance();
    int chunksx = camera->getPixWidth()/num;
    int chunksy = camera->getPixHeight()/num;

    Chunk chunk;
    chunk.startx = 0;
    chunk.starty = 0;

    for(int i=1; i<=3; i++) {
        if (i == 3) chunk.stopx = camera->getPixWidth();
        else chunk.stopx = chunk.startx + chunksx;
        for(int j=1; j<=3; j++){
            if (j==3) chunk.stopy = camera->getPixHeight();
            else chunk.stopy = chunk.starty + chunksy;
            queue.push(chunk);
            chunk.starty = chunk.stopy;
        }
        chunk.startx = chunk.stopx;
    }
}
