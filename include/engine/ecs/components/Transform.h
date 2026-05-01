#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/vec3.hpp>

namespace Component {
    struct Transform {
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    };
}

#endif //TRANSFORM_H