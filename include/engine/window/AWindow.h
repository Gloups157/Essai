#ifndef A_WINDOW_H
#define A_WINDOW_H

#include <memory>

#include "WindowSettings.h"

class AWindow {
public:
    virtual ~AWindow() = default;

    virtual void clear() = 0;
    virtual void draw() = 0;
    virtual void close() = 0;
    virtual void quit() = 0;
    virtual bool isActive() = 0;
    virtual void* getNative() = 0;

    [[nodiscard]] int getScreenWidth() const {
        return windowSettings->screenWidth;
    }

    [[nodiscard]] int getScreenHeight() const {
        return windowSettings->screenHeight;
    }

    [[nodiscard]] float getRatio() const {
        return static_cast<float>(windowSettings->screenWidth) / static_cast<float>(windowSettings->screenHeight);
    }

    std::weak_ptr<WindowSettings> getWindowSettings() {
        return windowSettings;
    }

protected:
    std::shared_ptr<WindowSettings> windowSettings;
};

#endif //A_WINDOW_H