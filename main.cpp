#include <iostream>
#include "GLUtils.h"
#include "Chessboard.h"

Chessboard* board;

void update() {

}

void drawAxes() {
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

}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxes();
    glColor3f(1.0, 1.0, 1.0);
    board->render(0, 0);
    glutSwapBuffers();
}

/**
 * @brief Set timer to run every 1000 / SCREEN_FPS ms
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
    glutDisplayFunc(render);

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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "Error initializing OpenGL! " << gluErrorString(err) << "\n";
        return 1;
    }

    board = new Chessboard(3, 0.2);

    glutMainLoop();
    free(board);
    return 0;
}
