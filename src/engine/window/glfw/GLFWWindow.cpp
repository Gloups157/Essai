#include "../../../../include/engine/window/glfw/GLFWWindow.h"

#include <iostream>

GLFWWindow::GLFWWindow(const std::shared_ptr<WindowSettings>& windowSettings) {
    this->windowSettings = windowSettings;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    native = glfwCreateWindow(windowSettings->screenWidth, windowSettings->screenHeight, windowSettings->title, NULL, NULL);
    if (native == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(native);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
    glfwSetFramebufferSizeCallback(native, framebufferSizeCallback);
    glEnable(GL_DEPTH_TEST);
}

void GLFWWindow::clear() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLFWWindow::draw() {
    glfwSwapBuffers(native);
}

void GLFWWindow::close() {
    glfwSetWindowShouldClose(native, true);
}

void GLFWWindow::quit() {
    glfwTerminate();
}

bool GLFWWindow::isActive() {
    return !glfwWindowShouldClose(native);
}

void* GLFWWindow::getNative() {
    return native;
}

void GLFWWindow::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
