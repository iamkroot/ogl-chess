#ifndef LOPENGL_H
#define LOPENGL_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Color.h"

#define DEBUG
#ifdef DEBUG
#define casePrint(val) case val: std::cout<<#val<<std::endl; break;
#endif

#endif //LOPENGL_H
