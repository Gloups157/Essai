#ifndef ENGINE_CONTEXT_H
#define ENGINE_CONTEXT_H

#include <utility>

#include "../time/ATime.h"
#include "../window/AWindow.h"
#include "../input/AInput.h"
#include "../renderer/ARenderer.h"

#include "Camera.h"

struct EngineContext {
    std::shared_ptr<ATime> time;
    std::shared_ptr<AWindow> window;
    std::shared_ptr<AInput> input;
    std::shared_ptr<ARenderer> renderer;
    std::shared_ptr<Camera> camera;

    EngineContext(std::shared_ptr<ATime> time, std::shared_ptr<AWindow> window, std::shared_ptr<AInput> input, std::shared_ptr<ARenderer> renderer, std::shared_ptr<Camera> camera) :
    time(std::move(time)),
    window(std::move(window)),
    input(std::move(input)),
    renderer(std::move(renderer)),
    camera(std::move(camera)) {}
};

#endif //ENGINE_CONTEXT_H