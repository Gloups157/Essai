#ifndef TIME_FACTORY_H
#define TIME_FACTORY_H

#include <memory>
#include <stdexcept>
#include "glfw/GLFWTime.h"
#include "engine/window/EWindowBackend.h"

class TimeFactory {
public:
    static std::shared_ptr<ATime> create(const EWindowBackend windowBackend) {
        switch (windowBackend) {
        case EWindowBackend::GLFW:
                return std::make_shared<GLFWTime>();
            case EWindowBackend::SDL:
                return std::make_shared<GLFWTime>();
            default:
                throw std::runtime_error("Unknown backend");
        }
    }
};

#endif //TIME_FACTORY_H