#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <string>
#include <vector>
#include "glm/glm.hpp"

class ObjModel {
    std::vector<glm::vec3> vertices, normals;
    std::vector<std::vector<std::pair<int, int>>> triangles;
    unsigned int listIndex{0};

public:
    ObjModel();

    explicit ObjModel(const char* path);

    void load(const char* path);

    void render();

    glm::vec3 lowestVertex{0, std::numeric_limits<float>::max(), 0};
};


#endif //OBJMODEL_H
