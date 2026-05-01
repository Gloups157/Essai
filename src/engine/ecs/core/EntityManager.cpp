#include "engine/ecs/core/EntityManager.h"

EntityManager::EntityManager() {
    entities.reserve(MAX_ENTITIES);
    componentSparseSets.reserve(MAX_COMPONENTS);
    typeToId.reserve(MAX_COMPONENTS);
    idToType.reserve(MAX_COMPONENTS);
}

void EntityManager::deleteEntity(const EntityId entity) {
    if (entityExist(entity)) {
        entities[entity] = entities.back();
        entities.pop_back();
        for (auto componentSparseSet : componentSparseSets) {
            componentSparseSet.second->removeComponent(entity);
        }
    }
}

bool EntityManager::entityExist(const EntityId entity) {
    return entity < entities.size();
}

bool EntityManager::entityHasSignature(const EntityId entity, const Signature& signature) {
    return (entities.at(entity) & signature) == signature;
}

EntityId EntityManager::createEntity() {
    if (entities.size() < MAX_ENTITIES) {
        entities.emplace_back(0);
        return entities.size() - 1;
    }
    return MAX_ENTITIES;
}

Signature EntityManager::getEntitySignature(const EntityId entity) {
    return entities.at(entity);
}

Signature EntityManager::getComponentSignature(const ComponentId component) {
    Signature signature;
    signature.set(component);
    return signature;
}

Signature EntityManager::getSignature(const std::vector<ComponentId>& components) {
    Signature signature;
    for (const auto& component : components) {
        signature.set(component);
    }
    return signature;
}
