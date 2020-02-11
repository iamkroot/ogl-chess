#ifndef LUTIL_H
#define LUTIL_H

#include "LOpenGL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

enum class COLOR_MODE {
    CYAN, MULTI
};

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

/**
 * @brief Handle keypress events
 * @li Toggles color mode when 'c' is pressed
 * @li Cycles through projection scales when `s` is pressed
 *
 * @param key
 * @param x
 * @param y
 */
void handleKeys(unsigned char key, int x, int y);

#endif //LUTIL_H