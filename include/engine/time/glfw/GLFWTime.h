#ifndef GLFW_TIME_H
#define GLFW_TIME_H

#include "../ATime.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class GLFWTime : public ATime {
public:
    void tick() override;
};

#endif //GLFW_TIME_H