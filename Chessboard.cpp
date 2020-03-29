#include "Chessboard.h"

Chessboard::Chessboard(GLint cbWidth, GLint cbHeight) : CBWidth(cbWidth), CBHeight(cbHeight) {}

bool Chessboard::initBaseBoard() {
    const GLint CBPixelCount = CBWidth * CBHeight;
    GLuint checkerBoard[CBPixelCount];
    for (unsigned int i = 0; i < CBPixelCount; ++i) {
        auto colors = (GLubyte*) &checkerBoard[i];
        if ((i >> 7u & 16u) ^ (i & 16u)) {
            colors[0] = colors[1] = colors[2] = colors[3] = 0xff;
        } else {
            colors[0] = colors[1] = colors[2] = colors[3] = 0x00;
        }
    }
    if (!checkBoard.loadTextureFromPixels32(checkerBoard, CBWidth, CBHeight)) {
        std::cerr << "Unable to load texture.\n";
        return false;
    }
    return true;
}

void Chessboard::render(GLint x, GLint y) {
    checkBoard.render(x, y);
}
