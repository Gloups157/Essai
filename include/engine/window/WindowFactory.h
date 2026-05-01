#ifndef WINDOW_FACTORY_H
#define WINDOW_FACTORY_H

#include <stdexcept>
#include "AWindow.h"
#include "glfw/GLFWWindow.h"
#include "EWindowBackend.h"

class WindowFactory {
public:
    static std::shared_ptr<AWindow> create(const EWindowBackend windowBackend, std::shared_ptr<WindowSettings> windowSettings) {
        switch (windowBackend) {
            case EWindowBackend::GLFW:
                return std::make_shared<GLFWWindow>(windowSettings);
            case EWindowBackend::SDL:
                return std::make_shared<GLFWWindow>(windowSettings);
            default:
                throw std::runtime_error("Unknown backend");
        }
    }
};

#endif //WINDOW_FACTORY_H