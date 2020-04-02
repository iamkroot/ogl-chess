#ifndef LOPENGL_H
#define LOPENGL_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <iostream>


#define DEBUG
#ifdef DEBUG
#define casePrint(val) case val: std::cout<<#val<<std::endl; break;
#endif

namespace Colors {
    const float
            WHITE[] = {1, 1, 1, 1},
            WHITE_PIECE[] = {0.4, 0.4, 0.4, 1},
            BLACK_PIECE[] = {0.1, 0.1, 0.1, 1},
            RED[] = {1, 0, 0, 1},
            GREEN[] = {0, 1, 0, 1},
            BLUE[] = {0, 0, 1, 1},
            YELLOW[] = {0, 1, 1, 1};
}
#endif //LOPENGL_H
