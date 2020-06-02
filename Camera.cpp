#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

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
    auto rolledRight = glm::rotate(right, glm::radians(roll), front);
    up = glm::normalize(glm::cross(rolledRight, front));
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
    initRoll = roll = 0;
    updateVectors();
}

void Camera::reset() {
    position = initPosition;
    yaw = initYaw;
    pitch = initPitch;
    roll = initRoll;
    zoomFactor = 1;
    updateVectors();
}

void Camera::rotate(int x, int y) {
    yaw -= rotationSensitivity * (float) x;
    pitch += rotationSensitivity * (float) y;
    yaw = glm::clamp(yaw, initYaw - 90.f, initYaw + 90.f);
    pitch = glm::clamp(pitch, initPitch - 90.f, initPitch + 90.f);
    updateVectors();
}

void Camera::rotate(int z) {
    roll += rotationSensitivity * (float) z;
    if (roll >= 360)
        roll -= 360;
    else if (roll <= -360.f)
        roll += 360;
    updateVectors();
}

void Camera::zoom(int y) {
    zoomFactor -= (float) y * zoomSensitivity;
    zoomFactor = std::max(zoomFactor, 0.05f);
    zoomFactor = std::min(zoomFactor, 20.f);
}

GLfloat Camera::getZoom() const {
    return zoomFactor;
}
