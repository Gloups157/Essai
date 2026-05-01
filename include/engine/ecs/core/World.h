#ifndef WORLD_H
#define WORLD_H

#include "EntityManager.h"
#include "SystemManager.h"
#include "core/utilities/helpers/AActivable.h"

class World : public Core::AActivable, public ILifeCycle {
public:
    World();
    ~World() override = default;

    void initialize() override;
    void start() override;
    void update() override;
    void fixedUpdate() override;
    void lateUpdate() override;

    template<typename T, typename... Args>
    void registerSystem(Args&&... args) {
        systemManager->registerSystem<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    void unregisterSystem() {
        systemManager->unregisterSystem<T>();
    }

    std::weak_ptr<EntityManager> getEntityManager();
    std::weak_ptr<SystemManager> getSystemManager();

private:
    std::shared_ptr<EntityManager> entityManager;
    std::shared_ptr<SystemManager> systemManager;
};

#endif //WORLD_H