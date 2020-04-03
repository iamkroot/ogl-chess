#ifndef CAMERA_H
#define CAMERA_H

#include "LOpenGL.h"

class Camera {
    GLfloat yaw;
    GLfloat pitch;
    GLfloat initYaw;
    GLfloat initPitch;
    GLfloat translationSensitivity = 1;
    GLfloat rotationSensitivity = 0.2;
    GLfloat zoomSensitivity = 0.1;
    GLfloat zoomFactor = 1;
    glm::vec3 position;
    glm::vec3 initPosition;
    glm::vec3 up;
    glm::vec3 worldUp{0, 1, 0};
    glm::vec3 front;
    glm::vec3 right;

    void updateVectors();

public:
    enum class Direction {
        FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN
    };

    Camera(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &worldUp = {0, 1, 0});

    void translate(Camera::Direction direction);

    void lookAt();

    void reset();

    void rotate(int x, int y);

    void zoom(int y);

    GLfloat getZoom();
};

#endif //CAMERA_H
