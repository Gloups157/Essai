#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include <memory>

#include "../AWindow.h"
#include "../../renderer/opengl/OpenGLCore.h"

class GLFWWindow : public AWindow {
public:
    GLFWWindow(const std::shared_ptr<WindowSettings>& windowSettings);
    void clear() override;
    void draw() override;
    void close() override;
    void quit() override;
    bool isActive() override;
    void* getNative() override;

private:
    GLFWwindow* native = nullptr;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

#endif //GLFW_WINDOW_H