#ifndef RENDERER_SYSTEM_H
#define RENDERER_SYSTEM_H

#include <iostream>

#include "engine/core/Camera.h"
#include "engine/ecs/core/ASystem.h"
#include "engine/ecs/components/Renderer2D.h"

class RendererSystem : public ASystem {
public:
    RendererSystem(const std::weak_ptr<EngineContext>& context, const std::weak_ptr<EntityManager>& entityManager) : ASystem(context, entityManager) {}
    void initialize() override {}
    void start() override {}
    void update() override {
        if (auto locked = context.lock()) {
            auto results = query.search<Component::Transform, Component::Renderer2D>();
            for (auto& [entity, transform, renderer] : results) {
                if (locked->renderer->shouldFlush()) {
                    locked->renderer->flush(locked->camera->view(), locked->camera->project(locked->window));
                }
                locked->renderer->addSprite(transform, renderer);
            }
            if (!locked->renderer->isBufferEmpty()) {
                locked->renderer->flush(locked->camera->view(), locked->camera->project(locked->window));
                std::cout << "Flush final" << std::endl;
            }
        }
    }
    void fixedUpdate() override {}
    void lateUpdate() override {}
};

#endif //RENDERER_SYSTEM_H