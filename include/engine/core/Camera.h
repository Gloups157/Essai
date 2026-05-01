#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include <glm/glm.hpp>
#include "../input/AInput.h"
#include "engine/time/ATime.h"
#include "engine/window/AWindow.h"

class Camera {
public:
    Camera();
    void initialize(const std::weak_ptr<AInput>& input);
    glm::mat4 view();
    glm::mat4 project(const std::weak_ptr<AWindow>& window);
    void move(const std::weak_ptr<AInput>& input, const std::weak_ptr<ATime>& time);

private:
    float yaw;
    float pitch;
    float fov;
    float speed;
    glm::vec3 position;
    glm::vec3 frontDirection;
    glm::vec3 upDirection;

    void look(float x, float y);
    void zoom(float x, float y);
};

#endif //CAMERA_H