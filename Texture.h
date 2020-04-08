#ifndef TEXTURE_H
#define TEXTURE_H

#include "LOpenGL.h"
#include <iostream>

class Texture {
    GLuint texID;
    GLuint width;
    GLuint height;
public:
    Texture();

    ~Texture();

    /**
     * @brief Load and create the glTexture
     * @param pixels The source image
     * @param width Width of source
     * @param height Height of source
     * @return Success
     */
    bool load(GLuint* pixels, GLuint width, GLuint height);

    /**
     * @brief Clear memory used by texture
     */
    void freeTexture();

    /**
     * Get ID of texture
     */
    GLuint getID();
};


#endif //TEXTURE_H
