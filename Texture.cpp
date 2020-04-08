#include "Texture.h"

Texture::Texture() {
    texID = 0;
    width = 0;
    height = 0;
}

Texture::~Texture() {
    freeTexture();
}

bool Texture::load(GLuint* pixels, GLuint width, GLuint height) {
    freeTexture();
    width = width;
    height = height;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "Error loading textures: " << gluErrorString(err) << "\n";
        return false;
    }
    return true;
}

void Texture::freeTexture() {
    if (texID != 0) {
        glDeleteTextures(1, &texID);
        texID = 0;
    }
    width = 0;
    height = 0;
}

GLuint Texture::getID() {
    return texID;
}

