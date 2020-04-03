#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include "ObjModel.h"
#include "Texture.h"

class Chessboard {

public:
    Chessboard(GLdouble cbWidth, GLdouble cbHeight);

    enum class PIECE {
        BISHOP = 1, KING, KNIGHT, PAWN, QUEEN, ROOK
    };
    enum class PIECE_COLOR {
        WHITE, BLACK
    };

    void render(GLdouble x, GLdouble y);

private:
    Texture checkBoard;
    GLdouble CBWidth, CBHeight, cellWidth;
    std::map<PIECE, ObjModel> models;

    class Cell {
    public:
        PIECE piece;
        PIECE_COLOR color;

        Cell(PIECE piece, PIECE_COLOR color);

        Cell();

        [[nodiscard]] bool empty() const;
    };

    Cell board[8][8];

    bool initBaseBoard();

    void initPositions();

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

};


#endif //CHESSBOARD_H
