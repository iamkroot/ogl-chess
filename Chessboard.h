#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include "ObjModel.h"
#include "Texture.h"

class Chessboard {

public:

    /**
     * @brief Initialize the chessboard
     * @param width
     * @param thickness
     */
    Chessboard(GLdouble width, GLdouble thickness);

    enum class PIECE {
        BISHOP = 1, KING, KNIGHT, PAWN, QUEEN, ROOK
    };

    enum class PIECE_COLOR {
        WHITE, BLACK
    };

    /**
     * @brief Render the board and its pieces
     */
    void render();

    class Cell {
    public:
        PIECE piece;
        PIECE_COLOR color;

        Cell(PIECE piece, PIECE_COLOR color);

        Cell();

        /**
         * @brief Whether the cell contains a piece
         */
        [[nodiscard]] bool empty() const;
    };

    /**
     * @brief Square matrix representing the locations of the pieces
     */
    Cell board[8][8];
private:
    Texture checkBoard;
    GLdouble width, thickness, cellWidth;
    std::map<PIECE, ObjModel> models;
    static GLuint pawnList;

    /**
     * @brief Initialize the checkerboard texture of the board base
     * @return True if successful
     */
    bool initBaseBoard();

    /**
     * @brief Place the pieces on the board, as present at the beginning of a match
     */
    void initPositions();

    /**
     * @brief Translate to given cell on chessboard, assuming it was originally at center of board
     * @param file The column name, from 'a' to 'h', inclusive
     * @param rank The row number, from 1 to 8, inclusive
     */
    void translateTo(GLchar file, GLshort rank);

    /**
     * @brief Render the board base, by applying the texture on top face
     * @pre initBaseBoard() should have been called
     */
    void renderBaseBoard();

    /**
     * @brief Draws a pawn using OpenGL primitives
     * @param base How wide the base should be
     * @param height How tall the piece should be
     */
    static void drawPawn(GLdouble base, GLdouble height);

};


#endif //CHESSBOARD_H
