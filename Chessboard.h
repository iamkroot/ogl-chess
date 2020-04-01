#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Texture.h"

class Chessboard {
    Texture checkBoard;
    GLdouble CBWidth, CBHeight, cellWidth;

    bool initBaseBoard();

    /**
     * @brief Translate to given cell on chessboard, assuming it was originally at center of board
     * @param file The column name, from 'a' to 'h', inclusive
     * @param rank The row number, from 1 to 8, inclusive
     */
    void translateTo(GLchar file, GLshort rank);

    void renderBaseBoard();

    /**
     * @brief Draws a pawn using OpenGL primitives
     * @param base How wide the base should be
     * @param height How tall the piece should be
     */
    static void drawPawn(GLdouble base, GLdouble height);

    void renderPawns();

public:
    Chessboard(GLdouble cbWidth, GLdouble cbHeight);

    void render(GLdouble x, GLdouble y);
};


#endif //CHESSBOARD_H
