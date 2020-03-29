#include "GLUtils.h"
#include "Texture.h"

bool initGL() {
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "Error initializing OpenGL! " << gluErrorString(err) << "\n";
        return false;
    }
    return true;
}

void handleKeys(unsigned char key, int x, int y) {

}
