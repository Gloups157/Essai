#ifndef COMPONENT_SPARSE_SET_H
#define COMPONENT_SPARSE_SET_H

#include <cassert>
#include <unordered_map>
#include <vector>
#include "IComponentSparseSet.h"

template<typename T>
class ComponentSparseSet : public IComponentSparseSet {
public:
    explicit ComponentSparseSet(size_t capacity = MAX_ENTITIES) {
        components.reserve(capacity);
        indexToEntity.reserve(capacity);
        entityToIndex.reserve(capacity);
    }

    void addComponent(const EntityId entity, T& component) {
        if (!hasComponent(entity)) {
            entityToIndex[entity] = size();
            components.emplace_back(component);
            indexToEntity.emplace_back(entity);
        }
    }

    void copyComponent(const EntityId source, const EntityId destination) override {
        if (hasComponent(source) && !hasComponent(destination)) {
            addComponent(destination, getComponent(source));
        }
    }

    void removeComponent(const EntityId entity) override {
        if (hasComponent(entity)) {
            auto index = entityToIndex[entity];
            if (index < size() - 1) {
                components[index] = std::move(components.back());
                indexToEntity[index] = indexToEntity.back();
                entityToIndex[indexToEntity[index]] = index;
            }
            components.pop_back();
            indexToEntity.pop_back();
            entityToIndex.erase(entity);
        }
    }

    bool hasComponent(const EntityId entity) override {
        return entityToIndex.find(entity) != entityToIndex.end();
    }

    EntityId getEntityAt(const Index index) override {
        return indexToEntity[index];
    }

    size_t size() override {
        return components.size();
    }

    size_t capacity() override {
        return components.capacity();
    }

    T& getComponent(const EntityId entity) {
        assert(hasComponent(entity));
        return components[entityToIndex.at(entity)];
    }

    std::vector<T>& getComponents() {
        return components;
    }
private:
    // Dense
    std::vector<T> components;
    std::vector<EntityId> indexToEntity;
    // Sparse
    std::unordered_map<EntityId, Index> entityToIndex;
};

#endif //COMPONENT_SPARSE_SET_H