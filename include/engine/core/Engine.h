#ifndef ENGINE_H
#define ENGINE_H

#include "application/core/ApplicationLayer.h"
#include "engine/ecs/core/Universe.h"

class Engine : public ApplicationLayer {
public:
    Engine();
    void run() override;
    void quit() override;
private:
    std::shared_ptr<EngineContext> context;
    std::unique_ptr<Universe> universe;

    void initializeMocks();
};

#endif //ENGINE_H