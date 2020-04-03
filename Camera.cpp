#include "Camera.h"

void Camera::translate(Camera::Direction direction) {
    switch (direction) {
        case Direction::FORWARD:
            position += front * translationSensitivity;
            break;
        case Direction::BACKWARD:
            position -= front * translationSensitivity;
            break;
        case Direction::RIGHT:
            position += right * translationSensitivity;
            break;
        case Direction::LEFT:
            position -= right * translationSensitivity;
            break;
        case Direction::UP:
            position += up * translationSensitivity;
            break;
        case Direction::DOWN:
            position -= up * translationSensitivity;
            break;
    }
    updateVectors();
}

void Camera::updateVectors() {
    front = glm::normalize(glm::vec3(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    ));
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
    std::cout << "F(" << front.x << ", " << front.y << ", " << front.z << ")" << std::endl;
    std::cout << "R(" << right.x << ", " << right.y << ", " << right.z << ")" << std::endl;
    std::cout << "U(" << up.x << ", " << up.y << ", " << up.z << ")" << std::endl;
}

void Camera::lookAt() {
    auto center = position + front;
    gluLookAt(position.x, position.y, position.z, center.x, center.y, center.z, up.x, up.y, up.z);
}

Camera::Camera(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &worldUp) : position(position),
                                                                                               initPosition(position),
                                                                                               worldUp(worldUp) {
    front = glm::normalize(target - position);
    initYaw = yaw = glm::degrees(atan2f(front.z, front.x));
    initPitch = pitch = glm::degrees(asinf(front.y));
    updateVectors();
}

void Camera::reset() {
    position = initPosition;
    yaw = initYaw;
    pitch = initPitch;
    zoomFactor = 1;
    updateVectors();
}

void Camera::rotate(int x, int y) {
    yaw -= rotationSensitivity * (float) x;
    pitch += rotationSensitivity * (float) y;
    updateVectors();
}

void Camera::zoom(int y) {
    zoomFactor -= (float) y * zoomSensitivity;
    zoomFactor = std::max(zoomFactor, 0.05f);
    zoomFactor = std::min(zoomFactor, 20.f);
}

GLfloat Camera::getZoom() {
    return zoomFactor;
}
