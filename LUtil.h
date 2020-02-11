#ifndef LUTIL_H
#define LUTIL_H

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
 * @brief Per frame logic
 */
void update();

/**
 * @brief Render the scene
 */
void render();

#endif //LUTIL_H