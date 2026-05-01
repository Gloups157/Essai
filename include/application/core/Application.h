#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationLayer.h"
#include "core/utilities/containers/TypeVector.h"

class Application {
public:
    Application() = default;
    ~Application() = default;

    void run() {
        for (auto& layer : layers.getAll()) {
            if (layer->isActive()) {
                layer->run();
            }
        }
    }

    void quit() {

    }

    template<typename T>
    void addLayer() {
        layers.add<T>();
    }

    template<typename T>
    void removeLayer() {
        layers.remove<T>();
    }

private:
    Core::TypeVector<ApplicationLayer> layers;
};

#endif //APPLICATION_H