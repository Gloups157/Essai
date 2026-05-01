#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "ASystem.h"
#include "core/utilities/containers/TypeVector.h"

class SystemManager : public ILifeCycle {
public:
    SystemManager() = default;
    ~SystemManager() override = default;

    void initialize() override;
    void start() override;
    void update() override;
    void fixedUpdate() override;
    void lateUpdate() override;

    template<typename T, typename... Args>
    void registerSystem(Args&&... args) {
        systems.add<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    void unregisterSystem() {
        systems.remove<T>();
    }

private:
    Core::TypeVector<ASystem> systems;
};

#endif //SYSTEM_MANAGER_H