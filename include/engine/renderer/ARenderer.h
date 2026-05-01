#ifndef A_RENDERER_H
#define A_RENDERER_H

#include <glm/fwd.hpp>
#include "core/Types.h"
#include "engine/ecs/components/Renderer2D.h"
#include "engine/ecs/components/Transform.h"

class ARenderer {
public:
    virtual ~ARenderer() = default;
    virtual void addSprite(const Component::Transform& transform, const Component::Renderer2D& renderer2D) = 0;
    virtual void flush(const glm::mat4& view, const glm::mat4& Projection) = 0;
    virtual void registerTexture(Core::AssetPath texturePath) = 0;
    virtual bool shouldFlush() = 0;
    virtual bool isBufferEmpty() = 0;
};

#endif //A_RENDERER_H