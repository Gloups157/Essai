#include "engine/core/Camera.h"

#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

Camera::Camera():
    yaw(-90.0f),
    pitch(0.0f),
    fov(45.0f),
    speed(6.0f),
    position(0.0f, 0.0f, 3.0f),
    frontDirection(0.0f, 0.0f, -1.0f),
    upDirection(0.0f, 1.0f, 0.0f) {}

void Camera::initialize(const std::weak_ptr<AInput>& input) {
    if (auto i = input.lock()) {
        i->registerMouseDeltaCallback(this, &Camera::look);
        i->registerMouseScrollCallback(this, &Camera::zoom);
    }
}

glm::mat4 Camera::view() {
    return glm::lookAt(position, position + frontDirection, upDirection);
}

glm::mat4 Camera::project(const std::weak_ptr<AWindow>& window) {
    if (auto w = window.lock()) {
        return glm::perspective(glm::radians(fov), w->getRatio(), 0.1f, 100.0f);
    }
    return {1.0f};
}

void Camera::move(const std::weak_ptr<AInput>& input, const std::weak_ptr<ATime>& time) {
    if (auto i = input.lock()) {
        if (auto t = time.lock()) {
            const float cameraSpeed = speed * t->getDeltaTime();
            if (i->isKeyPressed(EKey::W)) {
                position += cameraSpeed * frontDirection;
            }
            if (i->isKeyPressed(EKey::S)) {
                position -= cameraSpeed * frontDirection;
            }
            if (i->isKeyPressed(EKey::A)) {
                position -= glm::normalize(glm::cross(frontDirection, upDirection)) * cameraSpeed;
            }
            if (i->isKeyPressed(EKey::D)) {
                position += glm::normalize(glm::cross(frontDirection, upDirection)) * cameraSpeed;
            }
            if (i->isKeyPressed(EKey::SPACE)) {
                position += cameraSpeed * upDirection;
            }
            if (i->isKeyPressed(EKey::CONTROL)) {
                position -= cameraSpeed * upDirection;
            }
        }
    }
}

void Camera::look(float x, float y) {
    float sensitivity = 0.05f;
    yaw += x * sensitivity;
    pitch += y * sensitivity;
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    glm::vec3 direction;
    direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    direction.y = glm::sin(glm::radians(pitch));
    direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    frontDirection = glm::normalize(direction);
}

void Camera::zoom(float x, float y) {
    fov -= y * 0.5f;
    if (fov < 1.0f) {
        fov = 1.0f;
    }
    if (fov > 45.0f) {
        fov = 45.0f;
    }
}
