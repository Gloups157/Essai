#include "engine/ecs/core/Universe.h"

Universe::Universe() {
    worlds.reserve(MAX_WORLDS);
}

void Universe::initialize() {

}

void Universe::start() {

}

void Universe::update() {
    for (auto& world : worlds) {
        world.update();
    }
}

void Universe::fixedUpdate() {

}

void Universe::lateUpdate() {

}

void Universe::deleteWorld(const unsigned int worldId) {
    if (hasWorld(worldId)) {
        worlds.erase(worlds.begin() + worldId);
    }
}

void Universe::enableWorld(const unsigned int worldId) {
    worlds.at(worldId).enable();
}

void Universe::disableWorld(const unsigned int worldId) {
    worlds.at(worldId).disable();
}

bool Universe::hasWorld(const unsigned int worldId) const {
    return worldId < worlds.size();
}

World& Universe::createWorld() {
    return worlds.emplace_back();
}

World& Universe::getWorld(const unsigned int worldId) {
    return worlds.at(worldId);
}