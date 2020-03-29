#include <iostream>
#include "GLUtils.h"
#include "Chessboard.h"

Chessboard* board;

void update() {

}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    board->render(256, 256);

    glutSwapBuffers();
}

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
    board = new Chessboard(256, 256);
    board->initBaseBoard();
    glutDisplayFunc(render);
//    glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, 0);
    glutMainLoop();
    free(board);
    return 0;
}
