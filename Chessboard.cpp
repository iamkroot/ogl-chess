#include "Chessboard.h"

Chessboard::Chessboard(GLdouble cbWidth, GLdouble cbHeight) : CBWidth(cbWidth), CBHeight(cbHeight) {
    initBaseBoard();
    cellWidth = (CBWidth / 8);
}

bool Chessboard::initBaseBoard() {
    GLuint checkerBoard[64];
    for (unsigned int i = 0; i < 64; ++i) {
        auto colors = (GLubyte*) &checkerBoard[i];
        if ((i & 1) ^ ((i & 8) == 8))
            colors[0] = colors[1] = colors[2] = 0x00;
        else
            colors[0] = colors[1] = colors[2] = 0xff;
        colors[3] = 0xff;
    }
    if (!checkBoard.loadTextureFromPixels32(checkerBoard, 8, 8)) {
        std::cerr << "Unable to load texture.\n";
        return false;
    }
    return true;
}

void Chessboard::renderBaseBoard() {
    const int NUM_VERTICES = 8, NUM_FACES = 6;
    GLdouble corner = CBWidth / 2, raise = CBHeight / 2;
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

    // draw top face with checker pattern
    glBindTexture(GL_TEXTURE_2D, checkBoard.getTextureID());
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3dv(verts[faces[0][0]]);
    glTexCoord2f(1.0, 0.0);
    glVertex3dv(verts[faces[0][1]]);
    glTexCoord2f(1.0, 1.0);
    glVertex3dv(verts[faces[0][2]]);
    glTexCoord2f(0.0, 1.0);
    glVertex3dv(verts[faces[0][3]]);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // draw other faces normally
    glBegin(GL_QUADS);
    for (int i = 1; i < NUM_FACES; ++i) {
        glColor3f(0.6, 0.6, 0.6);
        for (int j = 0; j < 4; ++j) {
            glVertex3dv(verts[faces[i][j]]);
        }
    }
    glEnd();
}

void Chessboard::drawPawn(GLdouble base, GLdouble height) {
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(base, height, 50, 50);
    glutSolidTorus(base, 3 * base / 5, 50, 50);
    glTranslatef(0, 0, base);
    glPushMatrix();
    glScalef(1, 1, 0.5);
    glutSolidTorus(4 * base / 5, base / 5, 50, 50);
    glPopMatrix();
    glTranslatef(0, 0, height - base);
    glutSolidSphere(base, 50, 50);
    glTranslatef(0, 0, -base);
    glutSolidTorus(base / 2, base / 10, 50, 50);
    glPopMatrix();
}

void Chessboard::render(GLdouble x, GLdouble y) {
    renderBaseBoard();
    renderPawns();
}

void Chessboard::translateTo(GLchar file, GLshort rank) {
    GLfloat a1Pos = (CBWidth - cellWidth) / 2;
    file = file - 'a';
    rank--;
    glTranslatef(a1Pos - (rank * cellWidth), CBHeight / 2,
                 a1Pos - (file * cellWidth));
}

void Chessboard::renderPawns() {
    double scale = 0.15;
    glPushMatrix();
    translateTo('a', 2);
    glColor3f(1, 1, 1);
    for (int i = 0; i < 8; ++i) {
        drawPawn(CBWidth / 32, CBWidth * scale);
        glTranslatef(0, 0, -cellWidth);
    }
    glPopMatrix();

    glPushMatrix();
    translateTo('a', 7);
    glColor3f(0.2, 0.2, 0.2);
    for (int i = 0; i < 8; ++i) {
        drawPawn(CBWidth / 32, CBWidth * scale);
        glTranslatef(0, 0, -cellWidth);
    }
    glPopMatrix();
}
