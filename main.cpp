#include <iostream>
#include "GLUtils.h"
#include "Chessboard.h"
#include "Color.h"
#include "Camera.h"

Camera camera({5, 5, 5}, {0, 0, 0});
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

GLuint tableList = 0;

void drawTable(GLfloat sideLen, GLfloat thickness) {
    if (tableList) {
        glCallList(tableList);
        return;
    }
    tableList = glGenLists(1);
    glNewList(tableList, GL_COMPILE);

    // draw top using a squished cube
    glPushMatrix();
    glTranslatef(0, -thickness / 2, 0);
    glScalef(1, thickness / sideLen, 1);
    glutSolidCube(sideLen);
    glPopMatrix();

    // draw legs
    glPushMatrix();
    double halfLen = sideLen / 2, radius = sideLen / 32, height = sideLen;
    glTranslatef(halfLen - radius, -thickness, halfLen - radius);
    glRotatef(90, 1, 0, 0);
    glutSolidCylinder(radius, height, 50, 50);
    glTranslatef(-sideLen + 2 * radius, 0, 0);
    glutSolidCylinder(radius, height, 50, 50);
    glTranslatef(0, -sideLen + 2 * radius, 0);
    glutSolidCylinder(radius, height, 50, 50);
    glTranslatef(sideLen - 2 * radius, 0, 0);
    glutSolidCylinder(radius, height, 50, 50);
    glPopMatrix();
    glEndList();
    glCallList(tableList);
}

GLuint chairList = 0;

void drawChair(GLfloat sideLen, GLfloat thickness) {
    if (chairList) {
        glCallList(chairList);
        return;
    }
    chairList = glGenLists(1);
    glNewList(chairList, GL_COMPILE);
    // base
    glPushMatrix();
    glTranslatef(0, -thickness / 2, 0);
    glScalef(1, thickness / sideLen, 1);
    glutSolidCube(sideLen);
    glPopMatrix();

    // legs
    glPushMatrix();
    double halfLen = sideLen / 2, radius = sideLen / 24, height = sideLen;
    glTranslatef(halfLen - radius, -thickness, halfLen - radius);
    glRotatef(90, 1, 0, 0);
    glutSolidCylinder(radius, height, 50, 50);
    glTranslatef(-sideLen + 2 * radius, 0, 0);
    glutSolidCylinder(radius, height, 50, 50);
    glTranslatef(0, -sideLen + 2 * radius, 0);
    glutSolidCylinder(radius, height, 50, 50);
    glTranslatef(sideLen - 2 * radius, 0, 0);
    glutSolidCylinder(radius, height, 50, 50);
    glPopMatrix();

    // back support
    glPushMatrix();
    glTranslatef(halfLen - radius, height, halfLen - radius);
    glRotatef(90, 1, 0, 0);
    GLfloat del = (sideLen + radius) / 8;
    for (int i = 0; i < 8; ++i) {
        glutSolidCylinder(radius, height, 50, 50);
        glTranslatef(0, -del, 0);
    }
    glPopMatrix();

    // back support top
    glPushMatrix();
    glTranslatef(halfLen - radius, height + thickness / 2, 0);
    glScalef(2 * radius / sideLen, thickness / sideLen, 1);
    glutSolidCube(sideLen);
    glPopMatrix();
    glEndList();
    glCallList(chairList);
}

void render() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0 * camera.getZoom(), (GLdouble) SCREEN_WIDTH / SCREEN_HEIGHT, 1.0, 64.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera.lookAt();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glColor4fv(Colors::BROWN.rgba);
    glTranslatef(0, -5.4, 0);
    glScalef(1, 0.000001, 1);
    glutSolidCube(50);
    glPopMatrix();

    glColor4fv(Colors::TAWNY.rgba);
    drawTable(5, 0.4);

    glPushMatrix();
    glTranslatef(5, -1.8, 0);
    drawChair(3, 0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    glTranslatef(5, -1.8, 0);
    drawChair(3, 0.5);
    glPopMatrix();

    glColor4fv(Colors::WHITE.rgba);
    board->render();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
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
        case '[': // ACW roll
            camera.rotate(-5);
            break;
        case ']': // CW roll
            camera.rotate(5);
            break;
        case 'q':
            glutLeaveMainLoop();
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


void special(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            camera.translate(Camera::Direction::UP);
            break;
        case GLUT_KEY_DOWN:
            camera.translate(Camera::Direction::DOWN);
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

void ByrneFischerSetUp() {
    for (auto &i : board->board) {
        for (auto &j : i) {
            j = {};
        }
    }
    board->board[0][5] = {Chessboard::PIECE::KING, Chessboard::PIECE_COLOR::WHITE};
    board->board[7][6] = {Chessboard::PIECE::KING, Chessboard::PIECE_COLOR::BLACK};
    board->board[1][0] = {Chessboard::PIECE::PAWN, Chessboard::PIECE_COLOR::WHITE};
    board->board[1][5] = {Chessboard::PIECE::PAWN, Chessboard::PIECE_COLOR::WHITE};
    board->board[1][6] = {Chessboard::PIECE::PAWN, Chessboard::PIECE_COLOR::WHITE};
    board->board[1][7] = {Chessboard::PIECE::PAWN, Chessboard::PIECE_COLOR::WHITE};
    board->board[3][3] = {Chessboard::PIECE::PAWN, Chessboard::PIECE_COLOR::WHITE};
    board->board[6][0] = {Chessboard::PIECE::PAWN, Chessboard::PIECE_COLOR::BLACK};
    board->board[6][1] = {Chessboard::PIECE::PAWN, Chessboard::PIECE_COLOR::BLACK};
    board->board[6][5] = {Chessboard::PIECE::PAWN, Chessboard::PIECE_COLOR::BLACK};
    board->board[6][7] = {Chessboard::PIECE::PAWN, Chessboard::PIECE_COLOR::BLACK};
    board->board[5][2] = {Chessboard::PIECE::PAWN, Chessboard::PIECE_COLOR::BLACK};
    board->board[5][6] = {Chessboard::PIECE::PAWN, Chessboard::PIECE_COLOR::BLACK};
    board->board[7][0] = {Chessboard::PIECE::ROOK, Chessboard::PIECE_COLOR::BLACK};
    board->board[7][4] = {Chessboard::PIECE::ROOK, Chessboard::PIECE_COLOR::BLACK};
    board->board[0][3] = {Chessboard::PIECE::ROOK, Chessboard::PIECE_COLOR::WHITE};
    board->board[0][7] = {Chessboard::PIECE::ROOK, Chessboard::PIECE_COLOR::WHITE};
    board->board[2][0] = {Chessboard::PIECE::QUEEN, Chessboard::PIECE_COLOR::WHITE};
    board->board[5][1] = {Chessboard::PIECE::QUEEN, Chessboard::PIECE_COLOR::BLACK};
    board->board[2][5] = {Chessboard::PIECE::KNIGHT, Chessboard::PIECE_COLOR::WHITE};
    board->board[2][2] = {Chessboard::PIECE::KNIGHT, Chessboard::PIECE_COLOR::BLACK};
    board->board[4][2] = {Chessboard::PIECE::BISHOP, Chessboard::PIECE_COLOR::WHITE};
    board->board[3][2] = {Chessboard::PIECE::BISHOP, Chessboard::PIECE_COLOR::WHITE};
    board->board[6][6] = {Chessboard::PIECE::BISHOP, Chessboard::PIECE_COLOR::BLACK};
    board->board[3][6] = {Chessboard::PIECE::BISHOP, Chessboard::PIECE_COLOR::BLACK};
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
    glutSpecialFunc(special);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);

#ifndef NDEBUG
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
    ByrneFischerSetUp();
    glutMainLoop();
    free(board);
    return 0;
}
