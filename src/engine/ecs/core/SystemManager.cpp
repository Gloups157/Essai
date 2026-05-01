#include "engine/ecs/core/SystemManager.h"

void SystemManager::initialize() {
    for (auto& system : systems.getAll()) {
        system->initialize();
    }
}

void SystemManager::start() {
    for (auto& system : systems.getAll()) {
        system->start();
    }
}

void SystemManager::update() {
    for (auto& system : systems.getAll()) {
        system->update();
    }
}

void SystemManager::fixedUpdate() {
    for (auto& system : systems.getAll()) {
        system->fixedUpdate();
    }
}

void SystemManager::lateUpdate() {
    for (auto& system : systems.getAll()) {
        system->lateUpdate();
    }
}
