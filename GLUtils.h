#ifndef GLUTILS_H
#define GLUTILS_H

#include "LOpenGL.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_FPS = 60;

void GLAPIENTRY
glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
              const void* userParam);

/**
 * @brief Handle keypress events
 *
 * @param key
 * @param x
 * @param y
 */
void handleKeys(unsigned char key, int x, int y);

#endif //GLUTILS_H