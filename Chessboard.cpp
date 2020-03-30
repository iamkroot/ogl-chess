#include "Chessboard.h"

Chessboard::Chessboard(GLint cbWidth, GLint cbHeight) : CBWidth(cbWidth), CBHeight(cbHeight) {}

bool Chessboard::initBaseBoard() {
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
    if (!checkBoard.loadTextureFromPixels32(checkerBoard, 8, 8)) {
        std::cerr << "Unable to load texture.\n";
        return false;
    }
    return true;
}

void Chessboard::render(GLint x, GLint y) {
    checkBoard.render(x, y);
}
