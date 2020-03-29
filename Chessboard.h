#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Texture.h"

class Chessboard {
    Texture checkBoard;
    GLint CBWidth, CBHeight;
public:
    Chessboard(GLint cbWidth, GLint cbHeight);

    bool initBaseBoard();

    void render(GLint x, GLint y);
};


#endif //CHESSBOARD_H
