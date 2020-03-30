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

void drawBoardBase(GLdouble sideLen, GLdouble thickness) {
    GLuint checkerBoard[64];
    for (unsigned int i = 0; i < 64; ++i) {
        auto colors = (GLubyte*) &checkerBoard[i];
        if ((i & 1) ^ ((i & 8) == 8)) {
            colors[0] = colors[1] = colors[2] = colors[3] = 0xff;
        } else {
            colors[0] = colors[1] = colors[2] = 0x00;
            colors[3] = 0xff;
        }
    }
    Texture t;
    t.loadTextureFromPixels32(checkerBoard, 8, 8);
    const int NUM_VERTICES = 8, NUM_FACES = 6;
    GLdouble corner = sideLen / 2, raise = thickness / 2;
    GLdouble verts[NUM_VERTICES][3] = {
            {corner,  raise,  corner},
            {corner,  -raise, corner},
            {corner,  raise,  -corner},
            {corner,  -raise, -corner},
            {-corner, raise,  corner},
            {-corner, -raise, corner},
            {-corner, raise,  -corner},
            {-corner, -raise, -corner},
    };
    GLint faces[NUM_FACES][4] = {
            {4, 0, 2, 6},
            {1, 5, 7, 3},
            {5, 4, 6, 7},
            {3, 7, 6, 2},
            {0, 1, 3, 2},
            {0, 4, 5, 1}
    };
    for (int i = 0; i < NUM_FACES; ++i) {
        if (i == 0)
            glBindTexture(GL_TEXTURE_2D, t.getTextureID());
        else
            glBindTexture(GL_TEXTURE_2D, 0);
        glBegin(GL_QUADS);
        if (i == 0) {
            glTexCoord2f(0.0, 0.0);
            glVertex3dv(verts[faces[i][0]]);
            glTexCoord2f(1.0, 0.0);
            glVertex3dv(verts[faces[i][1]]);
            glTexCoord2f(1.0, 1.0);
            glVertex3dv(verts[faces[i][2]]);
            glTexCoord2f(0.0, 1.0);
            glVertex3dv(verts[faces[i][3]]);
        } else {
            glColor3f(0.6, 0.6, 0.6);
            for (int j = 0; j < 4; ++j) {
                glVertex3dv(verts[faces[i][j]]);
            }
        }
        glEnd();
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxes();
    glColor3f(1.0, 1.0, 1.0);
    drawBoardBase(3, 0.2);

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

    glutMainLoop();
    free(board);
    return 0;
}
