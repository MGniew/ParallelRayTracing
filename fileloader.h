#ifndef FILELOADER_H
#define FILELOADER_H

#include <cstring>
#include <string>
#include <sstream>
#include "camera.h"
#include "scene.h"
#include "vector3.h"
#include "sphere.h"


class FileLoader
{
public:
    FileLoader();
    bool ReadFile(const char* fname);

private:
    bool readCameraSettings(const char* line);
    bool readSceneSettings(const char* line);
    bool readSphere(const char* line);
    bool readLight(const char* line);
    bool readTriangle(const char* line);
    bool readObj(const char *line);

};

#endif // FILELOADER_H
