#ifndef LUTIL_H
#define LUTIL_H

#include "LOpenGL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

enum VIEWPORT_MODE {
    FULL,
    HALF_CENTER,
    HALF_TOP,
    QUAD,
    RADAR
};

/**
 * @brief Initialize matrices and clear color
 * @return success
 */
bool initGL();

/**
 * @brief Loads media to use in program
 * @return success
 */
bool loadMedia();

/**
 * @brief Per frame logic
 */
void update();

/**
 * @brief Render the scene
 */
void render();

/**
 * @brief Handle keypress events
 *
 * @param key
 * @param x
 * @param y
 */
void handleKeys(unsigned char key, int x, int y);

#endif //LUTIL_H