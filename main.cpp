#include <iostream>
#include "LUtil.h"

/**
 * @brief Set timer to run every 1000 / SCREEN_FPS ms
 * @param val
 */
void runMainLoop(int val) {
    update();
    render();
    glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, val);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitContextVersion(2, 1);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Chess");
    if (!initGL()) {
        return 1;
    }
    if (!loadMedia()) {
        return 2;
    }
    glutDisplayFunc(render);
    glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, 0);
    glutMainLoop();

    return 0;
}
