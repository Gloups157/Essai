#ifndef RENDERER_FACTORY_H
#define RENDERER_FACTORY_H

#include "ERendererBackend.h"
#include "ARenderer.h"
#include "opengl/OpenGLRenderer.h"

class RendererFactory {
public:
    static std::shared_ptr<ARenderer> create(const ERendererBackend rendererBackend) {
        switch (rendererBackend) {
        case ERendererBackend::OPEN_GL:
                return std::make_shared<OpenGLRenderer>();
            case ERendererBackend::VULKAN:
                return std::make_shared<OpenGLRenderer>();
            default:
                throw std::runtime_error("Unknown backend");
        }
    }
};

#endif //RENDERER_FACTORY_H