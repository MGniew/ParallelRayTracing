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

        //printf("%s\n",line);
    }
    fclose(file);
    return true;
}

bool FileLoader::readCameraSettings(const char *line)
{
    float posX, posY, posZ;
    float lookAtX, lookAtY, lookAtZ;
    float zNear, zFar;
    float povy;

    if (sscanf(line, "camera eye<%f; %f; %f> "
               "lookAt<%f; %f; %f> zNear<%f> "
               "zFar<%f> povy<%f>",
               &posX, &posY, &posZ, &lookAtX, &lookAtY, &lookAtZ, &zNear,
               &zFar, &povy) != 9) {
        return false;
    }

    Camera::getInstance(new Vector3<float>(posX, posY, posZ),
                        new Vector3<float>(lookAtX, lookAtY, lookAtZ),
                        zNear, zFar, povy);
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
    float pointAX, pointAY, pointAZ;
    float pointBX, pointBY, pointBZ;
    float pointCX, pointCY, pointCZ;
    float ambR, ambG, ambB;
    float difR, difG, difB;
    float specR, specG, specB;
    float specShin;
    float transparency;
    float mirror;
    float local;
    float density;

    if (sscanf(line, "triangle pointA<%f; %f; %f> pointB<%f; %f; %f> pointC<%f; %f; %f> "
               "amb<%f; %f; %f> dif<%f; %f; %f> spec<%f; %f; %f> specShin<%f> "
               "trans<%f> mirror<%f> local<%f> density<%f>",
               &pointAX, &pointAY, &pointAZ, &pointBX, &pointBY, &pointBZ,
               &pointCX, &pointCY, &pointCZ, &ambR, &ambG, &ambB,
               &difR, &difG, &difB, &specR, &specG, &specB, &specShin,
               &transparency, &mirror, &local, &density) != 23) {
        return false;
    }

    Scene::getInstance()->addObject(new Triangle(new Vector3<float>(pointAX, pointAY, pointAZ),
                                                 new Vector3<float>(pointBX, pointBY, pointBZ),
                                                 new Vector3<float>(pointCX, pointCY, pointCZ),
                                                 nullptr, nullptr, nullptr, 0,0,
                                                 new Vector3<float>(ambR, ambG, ambB),
                                                 new Vector3<float>(difR, difG, difB),
                                                 new Vector3<float>(specR, specG, specB),
                                                 specShin, transparency, mirror, local, density));

    return true;
}

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

   if(materials.empty()) {
       tinyobj::material_t defaultMaterial;
       tinyobj::InitMaterial(&defaultMaterial);
       materials.push_back(defaultMaterial);
   }

   if (!err.empty()) {
     std::cerr << err << std::endl;
   }

   if (!ret) {
      return false;
   }

   if (attrib.vertices.size() <= 0) return false;

   Vector3<float>** tabOfPoints = new Vector3<float>*[3];
   Vector3<float>** tabOfNormals = new Vector3<float>*[3];
   Vector3<float>* diffuseVector = nullptr;
   Vector3<float>* ambientVector = nullptr;
   Vector3<float>* specularVector = nullptr;



   for (size_t s = 0; s < shapes.size(); s++) {
     size_t index_offset = 0;
     for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
       int fv = shapes[s].mesh.num_face_vertices[f];

       for (size_t v = 0; v < fv; v++) {
         tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

         try {
             tabOfPoints[v] = new Vector3<float>(attrib.vertices.at(3*idx.vertex_index+0),
                                                 attrib.vertices.at(3*idx.vertex_index+1),
                                                 attrib.vertices.at(3*idx.vertex_index+2));
         }
         catch (const std::out_of_range& oor) {
             std::cerr << "Out of Range error - verticies: " << oor.what() << '\n';
             return false;
         }

         if (attrib.normals.size() > 0) {
             try {
                 tabOfNormals[v] = new Vector3<float>(attrib.normals.at(3*idx.normal_index+0),
                                                     attrib.normals.at(3*idx.normal_index+1),
                                                     attrib.normals.at(3*idx.normal_index+2));
             }
             catch (const std::out_of_range& oor) {
                 std::cerr << "Out of Range error: " << oor.what() << '\n';
                 return false;
             }
         }
         else {
             tabOfNormals[v] = nullptr;
         }

//         tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
//         tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];
       }
       index_offset += fv;

       // per-face material
       int current_material_id = shapes[s].mesh.material_ids[f];

       if ((current_material_id < 0) || (current_material_id >= static_cast<int>(materials.size()))) {
         current_material_id = 0;
        }

       diffuseVector = new Vector3<float>(materials[current_material_id].diffuse[0],
                                         materials[current_material_id].diffuse[1],
                                         materials[current_material_id].diffuse[2]);

       ambientVector = new Vector3<float>(materials[current_material_id].ambient[0],
                                         materials[current_material_id].ambient[1],
                                         materials[current_material_id].ambient[2]);

       specularVector = new Vector3<float>(materials[current_material_id].specular[0],
                                         materials[current_material_id].specular[1],
                                         materials[current_material_id].specular[2]);

       float shininess = materials[current_material_id].shininess;
       float ior = materials[current_material_id].ior; //index of reflection ~~ density
       float dissolve =  1 - materials[current_material_id].dissolve; //0 for fully transparent



       Scene::getInstance()->addObject(new Triangle(tabOfPoints[0], tabOfPoints[1], tabOfPoints[2],
                                                    tabOfNormals[0], tabOfNormals[1], tabOfNormals[2],
                                                    0, 0,
                                                    ambientVector, diffuseVector, specularVector, shininess,
                                                    dissolve, (1-dissolve)/3, 2*(1-dissolve)/3, ior));
     }


   }
   delete [] tabOfPoints;
   delete [] tabOfNormals;
return true;
}
