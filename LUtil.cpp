#include "LUtil.h"
#include "LTexture.h"

LTexture gCheckboardTex;

bool initGL() {
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f, 0.f, 0.f, 1.f);

    glEnable(GL_TEXTURE_2D);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "Error initializing OpenGL! " << gluErrorString(err) << "\n";
        return false;
    }
    return true;
}

bool loadMedia() {
    const int CB_WIDTH = 128;
    const int CB_HEIGHT = 128;
    const int CB_PIXEL_COUNT = CB_WIDTH * CB_HEIGHT;
    GLuint checkerBoard[CB_PIXEL_COUNT];
    for (unsigned int i = 0; i < CB_PIXEL_COUNT; ++i) {
        auto colors = (GLubyte*) &checkerBoard[i];
        if ((i >> 7u & 16u) ^ (i & 16u)) {
            colors[0] = colors[1] = colors[2] = colors[3] = 0xff;
        } else {
            colors[0] = colors[3] = 0xff;
            colors[1] = colors[2] = 0x00;
        }
    }
    if (!gCheckboardTex.loadTextureFromPixels32(checkerBoard, CB_WIDTH, CB_HEIGHT)) {
        std::cerr << "Unable to load texture.\n";
        return false;
    }
    return true;
}

void update() {

}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat x = ((float) SCREEN_WIDTH - gCheckboardTex.textureWidth()) / 2.f;
    GLfloat y = ((float) SCREEN_HEIGHT - gCheckboardTex.textureHeight()) / 2.f;
    gCheckboardTex.render(x, y);
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y) {

}
