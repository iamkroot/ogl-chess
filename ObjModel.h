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

    /**
     * @brief Parse and load the .obj file. Only supports vt, vn and f operations.
     * @param path
     */
    void load(const char* path);

    /**
     * @brief Renders the Display List of the model
     */
    void render();

    /**
     * @brief Required to place the object properly on the board
     */
    glm::vec3 lowestVertex{0, std::numeric_limits<float>::max(), 0};
};


#endif //OBJMODEL_H
