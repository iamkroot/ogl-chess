#include "LTexture.h"

LTexture::LTexture() {
    mTextureID = 0;
    mTextureWidth = 0;
    mTextureHeight = 0;
}

LTexture::~LTexture() {
    freeTexture();
}

bool LTexture::loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height) {
    freeTexture();
    mTextureWidth = width;
    mTextureHeight = height;
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "Error loading textures: " << gluErrorString(err) << "\n";
        return false;
    }
    return true;
}

void LTexture::freeTexture() {
    if (mTextureID != 0) {
        glDeleteTextures(1, &mTextureID);
        mTextureID = 0;
    }
    mTextureWidth = 0;
    mTextureHeight = 0;
}

void LTexture::render(GLfloat x, GLfloat y) {
    if (mTextureID == 0) {
        return;
    }
    glLoadIdentity();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.f, 0.f);
    glVertex2f(0.f, 0.f);
    glTexCoord2f(1.f, 0.f);
    glVertex2f(mTextureWidth, 0.f);
    glTexCoord2f(1.f, 1.f);
    glVertex2f(mTextureWidth, mTextureHeight);
    glTexCoord2f(0.f, 1.f);
    glVertex2f(0.f, mTextureHeight);
    glEnd();
}

GLuint LTexture::getTextureID() {
    return mTextureID;
}

GLuint LTexture::textureWidth() {
    return mTextureWidth;
}

GLuint LTexture::textureHeight() {
    return mTextureHeight;
}
