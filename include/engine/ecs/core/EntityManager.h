#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <typeindex>
#include <limits>
#include "ComponentSparseSet.h"

class EntityManager {
public:
    EntityManager();
    ~EntityManager() = default;
    void deleteEntity(EntityId entity);
    EntityId createEntity();

    template<typename T>
    void addComponent(const EntityId entity, T& component) {
        if (!entityHasComponent<T>(entity)) {
            registerComponent<T>();
            auto* componentSparseSet = getComponentSparseSet<T>();
            componentSparseSet->addComponent(entity, component);
            auto componentId = getComponentId<T>();
            entities[entity][componentId] = true;
        }
    }

    template<typename T>
    void copyComponent(const EntityId source, const EntityId destination) {
        if (entityHasComponent<T>(source) && !entityHasComponent<T>(destination)) {
            auto* componentSparseSet = getComponentSparseSet<T>();
            componentSparseSet->copyComponent(source, destination);
            auto componentId = getComponentId<T>();
            entities[destination][componentId] = entities[source][componentId];
        }
    }

    template<typename T>
    void removeComponent(const EntityId entity) {
        if (entityHasComponent<T>(entity)) {
            auto* componentSparseSet = getComponentSparseSet<T>();
            componentSparseSet->removeComponent(entity);
            auto componentId = getComponentId<T>();
            entities[entity][componentId] = false;
        }
    }

    template<typename T>
    T& getComponent(const EntityId entity) {
        return getComponentSparseSet<T>()->getComponent(entity);
    }

    template<typename... Ts>
    std::vector<EntityId> getEntitiesWithSignature() {
        auto components = getComponentsIds<Ts...>();
        Signature signature = getSignature(components);
        std::vector<EntityId> entitiesWithSignature;
        entitiesWithSignature.reserve(MAX_ENTITIES);
        for (EntityId entity = 0; entity < entities.size(); ++entity) {
            if (entityHasSignature(entity, signature)) {
                entitiesWithSignature.push_back(entity);
            }
        }
        return entitiesWithSignature;
    }

    template<typename... Ts>
    std::vector<std::tuple<EntityId,Ts&...>> search() {
        std::vector<std::tuple<EntityId,Ts&...>> response;
        std::vector<IComponentSparseSet*> queriesComponentSparseSets{ static_cast<IComponentSparseSet*>(getComponentSparseSet<Ts>())... };
        ComponentId smallestComponentSparseSetId = 0;
        auto smallestComponentSparseSetSize = std::numeric_limits<std::size_t>::max();
        for (auto i = 0; i < queriesComponentSparseSets.size(); ++i) {
            auto queryComponentSparseSetSize = queriesComponentSparseSets[i]->size();
            if (queryComponentSparseSetSize < smallestComponentSparseSetSize) {
                smallestComponentSparseSetId = i;
                smallestComponentSparseSetSize = queryComponentSparseSetSize;
            }
        }
        for (auto i = 0; i < smallestComponentSparseSetSize; ++i) {
            EntityId entity = queriesComponentSparseSets[smallestComponentSparseSetId]->getEntityAt(i);
            if ((entityHasComponent<Ts>(entity) && ...)) {
                response.emplace_back(entity, getComponent<Ts>(entity)...);
            }
        }
        return response;
    }

private:
    std::vector<Signature> entities;
    std::unordered_map<std::type_index, IComponentSparseSet*> componentSparseSets;
    std::unordered_map<std::type_index, ComponentId> typeToId;
    std::vector<std::type_index> idToType;

    bool entityExist(EntityId entity);
    bool entityHasSignature(EntityId entity, const Signature& signature);
    Signature getEntitySignature(EntityId entity);
    Signature getComponentSignature(ComponentId component);
    Signature getSignature(const std::vector<ComponentId>& components);

    template<typename T>
    void registerComponent() {
        if (!componentExist<T>()) {
            std::type_index type = typeid(T);
            componentSparseSets[type] = new ComponentSparseSet<T>();
            typeToId[type] = idToType.size();
            idToType.push_back(type);
        }
    }

    template<typename T>
    bool componentExist() {
        return typeToId.find(typeid(T)) != typeToId.end();
    }

    template<typename T>
    bool entityHasComponent(const EntityId entity) {
        if (entityExist(entity) && componentExist<T>()) {
            ComponentSparseSet<T>* componentSparseSet = getComponentSparseSet<T>();
            return componentSparseSet->hasComponent(entity);
        }
        return false;
    }

    template<typename T>
    ComponentId getComponentId() const {
        return typeToId.at(typeid(T));
    }

    template<typename... Ts>
    std::vector<ComponentId> getComponentsIds() const {
        return std::vector<ComponentId>{ getComponentId<Ts>()... };
    }

    template<typename T>
    ComponentSparseSet<T>* getComponentSparseSet() {
        std::type_index type = typeid(T);
        return static_cast<ComponentSparseSet<T>*>(componentSparseSets.at(type));
    }

    template<typename... Ts>
    IComponentSparseSet* getSmallestComponentSparseSet() {
        IComponentSparseSet* componentSparseSet = nullptr;
        ([&]() {
            ComponentSparseSet<Ts>* css = getComponentSparseSet<Ts>();
            if (componentSparseSet == nullptr || css->size() < componentSparseSet->size()) {
                componentSparseSet = css;
            }
        }(), ...);
        return componentSparseSet;
    }
};

#endif //ENTITY_MANAGER_H