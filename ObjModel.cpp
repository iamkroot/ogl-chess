#include "ObjModel.h"
#include "LOpenGL.h"
#include <iostream>
#include <fstream>
#include <sstream>

ObjModel::ObjModel() = default;

ObjModel::ObjModel(const char* path) {
    load(path);
}

void ObjModel::load(const char* path) {
    std::ifstream file(path);
    if (not file) {
        throw std::runtime_error(std::string("Unable to open ") + path);
    }
    vertices.clear();
    normals.clear();
    triangles.clear();
    std::string line, part;
    std::string header;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        ss >> header;

        if (header == "#" or header == "vt") {
            continue;
        }
        if (header == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (line.starts_with("v")) {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            if (vertex.y < lowestVertex.y)
                lowestVertex = vertex;
            vertices.push_back(vertex);
        } else if (line.starts_with("f")) {
            char c;
            std::vector<std::pair<int, int>> face;
            std::pair<int, int> vert_norm;
            for (int i = 0; i < 3; ++i) {
                ss >> vert_norm.first >> c >> c >> vert_norm.second;
                face.push_back(vert_norm);
            }
            triangles.push_back(face);
        }
    }
}

void ObjModel::render() {
    if (triangles.empty()) {
        throw std::runtime_error("Object model not loaded");
    }
    if (listIndex) {
        glCallList(listIndex);
        return;
    }
    listIndex = glGenLists(1);
    glNewList(listIndex, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    for (const auto &triangle : triangles) {
        for (const auto &vert_norm : triangle) {
            auto normal = normals[vert_norm.second - 1];
            auto vertex = vertices[vert_norm.first - 1];
            glNormal3fv(&normal[0]);
            glVertex3fv(&vertex[0]);
        }
    }
    glEnd();
    glEndList();
    glCallList(listIndex);
}
