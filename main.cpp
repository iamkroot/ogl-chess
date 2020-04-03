#include <iostream>
#include "GLUtils.h"
#include "Chessboard.h"
#include "Color.h"
#include "Camera.h"

Camera camera({5, 5, 0}, {0, 0, 0});
Chessboard* board;
GLboolean isDragging = false;
GLint dragX, dragY;

void drawAxes() {
    glBegin(GL_LINES);
    glColor4fv(Colors::RED.rgba);
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);
    glColor4fv(Colors::GREEN.rgba);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);
    glColor4fv(Colors::BLUE.rgba);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10);
    glEnd();

}

void render() {
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(45.0 * camera.getZoom(), (GLdouble) SCREEN_WIDTH / SCREEN_HEIGHT, 1.0, 64.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera.lookAt();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxes();
    glColor4fv(Colors::WHITE.rgba);
    board->render(0, 0);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    std::cout << key << std::endl;
    switch (key) {
        case 'w':
            camera.translate(Camera::Direction::FORWARD);
            break;
        case 's':
            camera.translate(Camera::Direction::BACKWARD);
            break;
        case 'a':
            camera.translate(Camera::Direction::LEFT);
            break;
        case 'd':
            camera.translate(Camera::Direction::RIGHT);
            break;
        case 'r':
            camera.reset();
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void mouseButton(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON: {
            if (state == GLUT_DOWN) {
                isDragging = true;
                dragX = x;
                dragY = y;
            } else {
                isDragging = false;
            }
            break;
        }
        case 3:
            camera.zoom(1);
            break;
        case 4:
            camera.zoom(-1);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void mouseMotion(int x, int y) {
    if (isDragging) {
        camera.rotate(x - dragX, y - dragY);
        dragX = x;
        dragY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitContextVersion(2, 1);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Chess");

    glewExperimental = GL_TRUE;
    glewInit();
    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);

#ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(glDebugOutput, nullptr);
#endif

    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glLightfv(GL_LIGHT0, GL_AMBIENT, Colors::WHITE.rgba);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "Error initializing OpenGL! " << gluErrorString(err) << "\n";
        return 1;
    }

    glClearColor(palette.bg.rgba[0], palette.bg.rgba[1], palette.bg.rgba[2], palette.bg.rgba[3]);

    board = new Chessboard(3, 0.2);

    glutMainLoop();
    free(board);
    return 0;
}
