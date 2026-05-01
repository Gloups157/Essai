#ifndef I_COMPONENT_SPARSE_SET_H
#define I_COMPONENT_SPARSE_SET_H

#include "ECSTypes.h"

class IComponentSparseSet {
public:
    virtual ~IComponentSparseSet() = default;
    virtual void copyComponent(EntityId source, EntityId destination) = 0;
    virtual void removeComponent(EntityId entity) = 0;
    virtual bool hasComponent(EntityId entity) = 0;
    virtual EntityId getEntityAt(Index index) = 0;
    virtual size_t size() = 0;
    virtual size_t capacity() = 0;
};

#endif //I_COMPONENT_SPARSE_SET_H