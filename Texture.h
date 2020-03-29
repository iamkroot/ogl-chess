#ifndef TEXTURE_H
#define TEXTURE_H

#include "LOpenGL.h"
#include <iostream>

class Texture {
public:
    Texture();

    ~Texture();

    bool loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height);

    void freeTexture();

    void render(GLfloat x, GLfloat y);

    GLuint getTextureID();

    GLuint textureWidth();

    GLuint textureHeight();

private:
    GLuint mTextureID;
    GLuint mTextureWidth;
    GLuint mTextureHeight;
};


#endif //TEXTURE_H
