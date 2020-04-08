#ifndef GLUTILS_H
#define GLUTILS_H

#include "LOpenGL.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

/**
 * @brief Callback to log all the messages by opengl for easy debugging
 */
void GLAPIENTRY
glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
              const void* userParam);

#endif //GLUTILS_H