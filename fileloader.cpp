#include "fileloader.h"

FileLoader::FileLoader()
{

}

bool FileLoader::ReadFile(const char *fname)
{
    FILE* file;
    file = fopen(fname, "r");
    if (file == nullptr) {
        perror("Error while reading scene file: ");
    }

    char line[256];
    int lineNum = 0;
    while(fgets(line, sizeof(line), file)) {

        char objectType[16];
        if (sscanf(line, "%15s", objectType) != 1) {
            continue;
        }
        bool test = true;

        if(strcmp(objectType, "sphere") == 0)
            test = readSphere(line);
        else if(strcmp(objectType, "light") == 0)
            test = readLight(line);
        else if(strcmp(objectType, "camera") == 0)
            test = readCameraSettings(line);
        else if(strcmp(objectType, "scene") == 0)
            test = readSceneSettings(line);
        else if(strcmp(objectType, "triangle") == 0)
            test = readTriangle(line);
        else if(strcmp(objectType, "obj") == 0)
            test = readObj(line);
        else
            continue;

        if(test) {
            fprintf(stderr, "An error ocured on line %d", lineNum);
            return false;
        }

        lineNum ++;
    }
    fclose(file);
    return true;
}

bool FileLoader::readCameraSettings(const char *line)
{
    float posX, posY, posZ;
    float rotX, rotY, rotZ;
    float zNear, zFar;
    float width, height;
    float povy;

    if (sscanf(line, "camera %f %f %f %f %f %f %f %f %f %f %f",
               &posX, &posY, &posZ, &rotX, &rotY, &rotZ, &zNear,
               &zFar, &width, &height, &povy) != 11) {
        return false;
    }

    Camera::getInstance(new Vector3<float>(posX, posY, posZ),
                        rotX, rotY, rotZ, zNear, zFar,
                        width, height, povy);

    return true;
}

bool FileLoader::readSceneSettings(const char *line)
{
    float r, g, b;
    float ambR, ambG, ambB;
    if (sscanf(line, "scene %f %f %f %f %f %f",
               &r, &g, &b, &ambR, &ambG, &ambB) != 6) {
        return false;
    }
    Scene::getInstance()->setBackgroundColor(r, g, b);
    Scene::getInstance()->setGlobalAmbient(ambR, ambG, ambB);
    return true;
}

//TODO: add addSphere function to scene.h
bool FileLoader::readSphere(const char *line)
{
    float ambR, ambG, ambB;
    float difR, difG, difB;
    float specR, specG, specB;
    float specShin;
    float posX, posY, posZ;
    float radius;
    float trans, mirror, local;
    float density;

    if (sscanf(line, "scene %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
               &ambR, &ambG, &ambB, &difR, &difG, &difB, &specR, &specG, &specB,
               &specShin, &posX, &posY, &posZ, &radius, &trans, &mirror, &local,
               &density) != 18) {
        return false;
    }
    return true;
}

//TODO: add addLight function to scene.h
bool FileLoader::readLight(const char *line)
{
    float posX, posY, posZ;
    float ambR, ambG, ambB;
    float difR, difG, difB;
    float specR, specG, specB;

    if (sscanf(line, "scene %f %f %f %f %f %f %f %f %f %f %f %f",
               &posX, &posY, &posZ, &ambR, &ambG, &ambB,
               &difR, &difG, &difB, &specR, &specG, &specB) != 12) {
        return false;
    }

    return true;
}

bool FileLoader::readTriangle(const char *line)
{
return true;
}

bool FileLoader::readObj(const char *line)
{
return true;
}
