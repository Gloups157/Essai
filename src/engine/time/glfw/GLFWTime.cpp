#include "../../../../include/engine/time/glfw/GLFWTime.h"

void GLFWTime::tick() {
    auto currentTime = static_cast<float>(glfwGetTime());
    deltaTime = currentTime - lastTick;
    lastTick = currentTime;
}