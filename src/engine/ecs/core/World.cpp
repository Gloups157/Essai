#include "engine/ecs/core/World.h"

World::World() :
    entityManager(std::make_shared<EntityManager>()),
    systemManager(std::make_shared<SystemManager>()) {}

void World::initialize() {
    systemManager->initialize();
}

void World::start() {
    systemManager->start();
}

void World::update() {
    systemManager->update();
}

void World::fixedUpdate() {
    systemManager->fixedUpdate();
}

void World::lateUpdate() {
    systemManager->lateUpdate();
}

std::weak_ptr<EntityManager> World::getEntityManager() {
    return entityManager;
}

std::weak_ptr<SystemManager> World::getSystemManager() {
    return systemManager;
}
