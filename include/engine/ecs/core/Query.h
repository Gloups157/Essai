#ifndef QUERY_H
#define QUERY_H

#include <memory>
#include "EntityManager.h"

class Query {
public:
    Query(const std::weak_ptr<EntityManager>& entityManager) {
        if (auto locked = entityManager.lock()) {
            this->entityManager = locked;
        }
        else {
            // error
        }
    }

    template<typename... Ts>
    std::vector<std::tuple<EntityId, Ts&...>> search() {
        if (auto locked = entityManager.lock()) {
            return locked->search<Ts...>();
        }
        else {
            return {};
            // error
        }
    }

private:
    std::weak_ptr<EntityManager> entityManager;
};

#endif //QUERY_H