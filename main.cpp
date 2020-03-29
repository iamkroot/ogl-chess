#include <iostream>
#include "GLUtils.h"
#include "Chessboard.h"

Chessboard* board;

void update() {

}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    board->render(0, 0);
    glColor3f(1.0, 1.0, 1.0);

    glutWireSphere(1, 50, 50);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10);
    glEnd();

    glutSwapBuffers();
}

/**
 * @brief Set timer to run every 1000 / SCREEN_FPS ms
 * @param val
 */
void runMainLoop(int val) {
    update();
    render();

}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitContextVersion(2, 1);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Chess");

    glewExperimental = GL_TRUE;
    glewInit();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble) SCREEN_WIDTH / SCREEN_HEIGHT, 1.0, 64.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4, 6, 5, 0, 0, 0, 0, 1, 0);

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(glDebugOutput, nullptr);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "Error initializing OpenGL! " << gluErrorString(err) << "\n";
        return false;
    }

    board = new Chessboard(256, 256);
    board->initBaseBoard();
    glutDisplayFunc(render);
//    glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, 0);
    glutMainLoop();
    free(board);
    return 0;
}
