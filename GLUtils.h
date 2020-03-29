#ifndef GLUTILS_H
#define GLUTILS_H

#include "LOpenGL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

/**
 * @brief Initialize matrices and clear color
 * @return success
 */
bool initGL();

/**
 * @brief Handle keypress events
 *
 * @param key
 * @param x
 * @param y
 */
void handleKeys(unsigned char key, int x, int y);

#endif //GLUTILS_H