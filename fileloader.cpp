#include "fileloader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

FileLoader::FileLoader()
{

}

bool FileLoader::ReadFile(const char *fname)
{
    Camera::getInstance();
    Scene::getInstance();

    FILE* file;
    file = fopen(fname, "r");
    if (file == nullptr) {
        perror("Error while reading scene file: ");
    }


    char line[256];
    int lineNum = 0;
    while(fgets(line, sizeof(line), file)) {
        char objectType[16];
        lineNum++;
        if (sscanf(line, "%15s", objectType) != 1) {
            continue;
        }
        bool test = true;

        char *cp = strrchr(line,'\r');
        if(cp != nullptr){
          *cp = '\0';
        }

        cp = strrchr(line,'\n');
        if(cp != nullptr){
          *cp = '\0';
        }

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

        if(!test) {
            fprintf(stderr, "An error occured on line %d", lineNum);
            return false;
        }

        printf("%s\n",line);
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

    if (sscanf(line, "camera eye<%f; %f; %f> rotationX<%f> "
               "rotationY<%f> rotationZ<%f> zNear<%f> "
               "zFar<%f> pixWidth<%f> pixHeight<%f> povy<%f>",
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
    if (sscanf(line, "scene background<%f; %f; %f> global<%f; %f; %f>",
               &r, &g, &b, &ambR, &ambG, &ambB) != 6) {
        return false;
    }
    Scene::getInstance()->setBackgroundColor(r, g, b);
    Scene::getInstance()->setGlobalAmbient(ambR, ambG, ambB);
    return true;
}

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

    if (sscanf(line, "sphere amb<%f; %f; %f> dif<%f; %f; %f> spec<%f; %f; %f> specShin<%f> "
               "pos<%f; %f; %f> radius<%f> trans<%f> mirror<%f> local<%f> density<%f>",
               &ambR, &ambG, &ambB, &difR, &difG, &difB, &specR, &specG, &specB,
               &specShin, &posX, &posY, &posZ, &radius, &trans, &mirror, &local,
               &density) != 18) {
        return false;
    }
    Scene::getInstance()->addObject(new Sphere(new Vector3<float>(ambR, ambG, ambB),
                                               new Vector3<float>(difR, difG, difB),
                                               new Vector3<float>(specR, specG, specB),
                                               specShin,
                                               new Vector3<float>(posX, posY, posZ),
                                               radius,
                                               trans, mirror, local,
                                               density));
    return true;
}


bool FileLoader::readLight(const char *line)
{
    float posX, posY, posZ;
    float ambR, ambG, ambB;
    float difR, difG, difB;
    float specR, specG, specB;

    if (sscanf(line, "light pos<%f; %f; %f> amb<%f; %f; %f> dif<%f; %f; %f> spec<%f; %f; %f>",
               &posX, &posY, &posZ, &ambR, &ambG, &ambB,
               &difR, &difG, &difB, &specR, &specG, &specB) != 12) {
        return false;
    }

    Scene::getInstance()->addLight(new Light(new Vector3<float>(posX, posY, posZ),
                                             new Vector3<float>(ambR, ambG, ambB),
                                             new Vector3<float>(difR, difG, difB),
                                             new Vector3<float>(specR, specG, specB)));

    return true;
}

bool FileLoader::readTriangle(const char *line)
{
    Scene::getInstance()->addObject(new Triangle());
    return true;
}


//WIP:
bool FileLoader::readObj(const char *line)
{


   const char *c = strrchr(line, ' ');
   if (!(c && *(c+1))) return false;
   c = c + 1;

   tinyobj::attrib_t attrib;
   std::vector<tinyobj::shape_t> shapes;
   std::vector<tinyobj::material_t> materials;

   std::string err;
   bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, c);

   if (!err.empty()) {
     std::cerr << err << std::endl;
   }

   if (!ret) {
      return false;
   }

   if (attrib.vertices.size() <= 0) return false;


   Vector3<float>** tabOfPoints = new Vector3<float>*[3];
   Vector3<float>** tabOfNormals = new Vector3<float>*[3];


   // Loop over shapes
   for (size_t s = 0; s < shapes.size(); s++) {
     // Loop over faces(polygon)
     size_t index_offset = 0;
     for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {

       int fv = shapes[s].mesh.num_face_vertices[f];
       //mine
       if (fv != 3) return false;
       //endmine

       // Loop over vertices in the face
       for (size_t v = 0; v < fv; v++) {
         // access to vertex
         tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
         try {
             tabOfPoints[v] = new Vector3<float>(attrib.vertices.at(3*idx.vertex_index+0),
                                                 attrib.vertices.at(3*idx.vertex_index+1),
                                                 attrib.vertices.at(3*idx.vertex_index+2));
         }
         catch (const std::out_of_range& oor) {
             std::cerr << "Out of Range error - verticies: " << oor.what() << '\n';
         }

         if (attrib.normals.size() > 0) {
             try {
             }
             catch (const std::out_of_range& oor) {
                 std::cerr << "Out of Range error: " << oor.what() << '\n';
             }
         }
         else {
              tabOfNormals[v] = new Vector3<float>(0,0,1);
         }

//         tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
//         tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];
       }
       index_offset += fv;

       // per-face material
//       shapes[s].mesh.material_ids[f];
       Scene::getInstance()->addObject(new Triangle(tabOfPoints[0], tabOfPoints[1], tabOfPoints[2],
                                                    tabOfNormals[0], tabOfNormals[1], tabOfNormals[2],
                                                    0, 0,
                                                    new Vector3<float>(0.5, 0.5, 0.5), new Vector3<float>(0.3, 0.3, 0.1),
                                                    new Vector3<float>(0.7, 0.7, 0.7), 39, 0.0, 0.0, 1.0, 0.0));
     }


   }
   std::cout << Scene::getInstance()->getNumOfObjects() << std::endl;
   delete [] tabOfPoints;
   delete [] tabOfNormals;
return true;
}
