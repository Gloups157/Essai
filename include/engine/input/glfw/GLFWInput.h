#ifndef GLFW_INPUT_H
#define GLFW_INPUT_H

#include "../AInput.h"

class GLFWInput : public AInput {
public:
    GLFWInput(void* nativeWindow);

    void update() override;

protected:
    static void updateKeyCallbacks(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void updateMouseButtonCallbacks(GLFWwindow* window, int button, int action, int mods);
    static void updateMouseCallbacks(GLFWwindow* window, double xpos, double ypos);
    static void updateMouseScrollCallbacks(GLFWwindow* window, double xoffset, double yoffset);
    static GLFWInput* getInstanceFromWindow(GLFWwindow* window);
    static EKey translateGLFWKey(int key);
    static EInputState translateGLFWInputState(int state);
};

#endif //GLFW_INPUT_H