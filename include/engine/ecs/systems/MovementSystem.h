#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "engine/input/EKey.h"
#include "engine/ecs/core/ASystem.h"

class MovementSystem : public ASystem {
public:
    MovementSystem(const std::weak_ptr<EngineContext>& context, const std::weak_ptr<EntityManager>& entityManager) : ASystem(context, entityManager) {}
    void initialize() override;
    void start() override;
    void update() override;
    void fixedUpdate() override;
    void lateUpdate() override;
    void move(EKey key);
};

#endif //MOVEMENT_SYSTEM_H