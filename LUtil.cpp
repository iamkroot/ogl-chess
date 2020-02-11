#include "LUtil.h"

COLOR_MODE gColorMode = COLOR_MODE::CYAN;
GLfloat gProjScale = 1.f;

bool initGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f, 0.f, 0.f, 1.f);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "Error initializing OpenGL! " << gluErrorString(err) << "\n";
        return false;
    }
    return true;
}

void update() {

}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch (gColorMode) {
        case COLOR_MODE::CYAN: {
            glBegin(GL_QUADS);
            glColor3f(0.f, 1.f, 1.f);
            glVertex2f(-50.f, -50.f);
            glVertex2f(50.f, -50.f);
            glVertex2f(50.f, 50.f);
            glVertex2f(-50.f, 50.f);
            glEnd();
            break;
        }
        case COLOR_MODE::MULTI: {
            glBegin(GL_QUADS);
            glColor3f(1.f, 0.f, 0.f);
            glVertex2f(-50.f, -50.f);
            glColor3f(1.f, 1.f, 0.f);
            glVertex2f(50.f, -50.f);
            glColor3f(0.f, 1.f, 0.f);
            glVertex2f(50.f, 50.f);
            glColor3f(0.f, 0.f, 1.f);
            glVertex2f(-50.f, 50.f);
            glEnd();
            break;
        }
    }
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'c': {
            gColorMode = gColorMode == COLOR_MODE::CYAN ? COLOR_MODE::MULTI : COLOR_MODE::CYAN;
            break;
        }
        case 's': {
            gProjScale *= 2;
            if (gProjScale > 2.f)
                gProjScale = 0.5f;
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0.0, SCREEN_WIDTH * gProjScale, SCREEN_HEIGHT * gProjScale, 0.0, 1.0, -1.0);
            break;
        }
        default:
            break;
    }
}
