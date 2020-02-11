#include "LUtil.h"

GLfloat gProjScale = 1.f;
VIEWPORT_MODE gViewPortMode = VIEWPORT_MODE::FULL;

bool initGL() {
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

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

    glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);

    switch (gViewPortMode) {
        case VIEWPORT_MODE::FULL: {
            glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            glBegin(GL_QUADS);
            glColor3f(1.f, 0.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f);
            glVertex2f(SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f);
            glVertex2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
            glVertex2f(-SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
            glEnd();
            break;
        }
        case VIEWPORT_MODE::HALF_CENTER: {
            glViewport(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            glBegin(GL_QUADS);
            glColor3f(0.f, 1.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f);
            glVertex2f(SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f);
            glVertex2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
            glVertex2f(-SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
            glEnd();
            break;
        }
        case VIEWPORT_MODE::HALF_TOP: {
            glViewport(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            glBegin(GL_QUADS);
            glColor3f(0.f, 0.f, 1.f);
            glVertex2f(-SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f);
            glVertex2f(SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f);
            glVertex2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
            glVertex2f(-SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
            glEnd();
            break;
        }
        case VIEWPORT_MODE::QUAD: {
            glViewport(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            glBegin(GL_QUADS);
            glColor3f(1.f, 0.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f(SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
            glVertex2f(-SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
            glEnd();

            glViewport(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            glBegin(GL_QUADS);
            glColor3f(0.f, 1.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f(SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
            glVertex2f(-SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
            glEnd();

            glViewport(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            glBegin(GL_QUADS);
            glColor3f(0.f, 0.f, 1.f);
            glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f(SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
            glVertex2f(-SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
            glEnd();

            glViewport(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
            glBegin(GL_QUADS);
            glColor3f(1.f, 1.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f(SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
            glVertex2f(-SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
            glEnd();
            break;
        }
        case VIEWPORT_MODE::RADAR: {
            glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            glBegin(GL_QUADS);
            glColor3f(1.f, 1.f, 1.f);
            glVertex2f(-SCREEN_WIDTH / 8.f, -SCREEN_HEIGHT / 8.f);
            glVertex2f(SCREEN_WIDTH / 8.f, -SCREEN_HEIGHT / 8.f);
            glVertex2f(SCREEN_WIDTH / 8.f, SCREEN_HEIGHT / 8.f);
            glVertex2f(-SCREEN_WIDTH / 8.f, SCREEN_HEIGHT / 8.f);
            glColor3f(0.f, 0.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 16.f, -SCREEN_HEIGHT / 16.f);
            glVertex2f(SCREEN_WIDTH / 16.f, -SCREEN_HEIGHT / 16.f);
            glVertex2f(SCREEN_WIDTH / 16.f, SCREEN_HEIGHT / 16.f);
            glVertex2f(-SCREEN_WIDTH / 16.f, SCREEN_HEIGHT / 16.f);
            glEnd();

            glViewport(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            glBegin(GL_QUADS);
            glColor3f(1.f, 1.f, 1.f);
            glVertex2f(-SCREEN_WIDTH / 8.f, -SCREEN_HEIGHT / 8.f);
            glVertex2f(SCREEN_WIDTH / 8.f, -SCREEN_HEIGHT / 8.f);
            glVertex2f(SCREEN_WIDTH / 8.f, SCREEN_HEIGHT / 8.f);
            glVertex2f(-SCREEN_WIDTH / 8.f, SCREEN_HEIGHT / 8.f);
            glColor3f(0.f, 0.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 16.f, -SCREEN_HEIGHT / 16.f);
            glVertex2f(SCREEN_WIDTH / 16.f, -SCREEN_HEIGHT / 16.f);
            glVertex2f(SCREEN_WIDTH / 16.f, SCREEN_HEIGHT / 16.f);
            glVertex2f(-SCREEN_WIDTH / 16.f, SCREEN_HEIGHT / 16.f);
            glEnd();
        }
    }
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'v': {
            int mode = gViewPortMode;
            if (mode < VIEWPORT_MODE::RADAR) {
                gViewPortMode = static_cast<VIEWPORT_MODE>(++mode);
            } else {
                gViewPortMode = VIEWPORT_MODE::FULL;
            }
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
