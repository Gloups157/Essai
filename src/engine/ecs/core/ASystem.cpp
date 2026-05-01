#include "engine/ecs/core/ASystem.h"

ASystem::ASystem(const std::weak_ptr<EngineContext>& context, const std::weak_ptr<EntityManager>& entityManager):
    context(context),
    query(entityManager),
    priority(SystemPriority::NONE) {}

Priority ASystem::getPriority() const {
    return priority;
}
