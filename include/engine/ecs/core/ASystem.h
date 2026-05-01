#ifndef A_SYSTEM_H
#define A_SYSTEM_H

#include "ILifeCycle.h"
#include "ECSTypes.h"
#include "engine/core/EngineContext.h"
#include "Query.h"

class ASystem : public ILifeCycle {
public:
    explicit ASystem(const std::weak_ptr<EngineContext>& context, const std::weak_ptr<EntityManager>& entityManager);
    ~ASystem() override = default;
    void initialize() override = 0;
    void start() override = 0;
    void update() override = 0;
    void fixedUpdate() override = 0;
    void lateUpdate() override = 0;
    [[nodiscard]] Priority getPriority() const;
protected:
    std::weak_ptr<EngineContext> context;
    Query query;
    Priority priority;
};

#endif //A_SYSTEM_H