#ifndef INPUT_FACTORY_H
#define INPUT_FACTORY_H

#include <stdexcept>
#include "AInput.h"
#include "glfw/GLFWInput.h"
#include "engine/window/EWindowBackend.h"

class InputFactory {
public:
    static std::shared_ptr<AInput> create(const EWindowBackend windowBackend, const std::shared_ptr<AWindow>& window) {
        switch (windowBackend) {
            case EWindowBackend::GLFW:
                return std::make_shared<GLFWInput>(window->getNative());
            case EWindowBackend::SDL:
                return std::make_shared<GLFWInput>(window->getNative());
            default:
                throw std::runtime_error("Unknown backend");
        }
    }
};

#endif //INPUT_FACTORY_H