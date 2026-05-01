#ifndef A_INPUT_H
#define A_INPUT_H

#include <functional>
#include <glm/vec2.hpp>
#include "EKey.h"
#include "InputInfo.h"
#include "EMouseButton.h"

using KeyCallback = std::function<void(EKey)>;
using MouseButtonCallback = std::function<void(EMouseButton)>;
using MousePositionCallback = std::function<void(float, float)>;
using MouseDeltaCallback = std::function<void(float, float)>;
using MouseScrollCallback = std::function<void(float, float)>;

class AInput {
public:
    AInput();
    virtual ~AInput() = default;

    virtual void update() = 0;

    void registerKeyCallback(const KeyCallback& callback);
    void registerMouseButtonCallback(const MouseButtonCallback &callback);
    void registerMousePositionCallback(const MousePositionCallback& callback);
    void registerMouseDeltaCallback(const MouseDeltaCallback& callback);
    void registerMouseScrollCallback(const MouseScrollCallback& callback);

    template<typename T>
    void registerKeyCallback(T* object, void (T::*method)(EKey key)) {
        keyCallbacks.push_back([object, method](EKey key) {
            (object->*method)(key);
        });
    }
    template<typename T>
    void registerMouseButtonCallback(T* object, void (T::*method)(EMouseButton mouse)) {
        mouseButtonCallbacks.push_back([object, method](EMouseButton mouse) {
            (object->*method)(mouse);
        });
    }
    template<typename T>
    void registerMousePositionCallback(T* object, void (T::*method)(float x, float y)) {
        mousePositionCallbacks.push_back([object, method](float x, float y) {
            (object->*method)(x, y);
        });
    }
    template<typename T>
    void registerMouseDeltaCallback(T* object, void (T::*method)(float x, float y)) {
        mouseDeltaCallbacks.push_back([object, method](float x, float y) {
            (object->*method)(x, y);
        });
    }
    template<typename T>
    void registerMouseScrollCallback(T* object, void (T::*method)(float x, float y)) {
        mouseScrollCallbacks.push_back([object, method](float x, float y) {
            (object->*method)(x, y);
        });
    }

    bool isKeyIdle(EKey key) const;
    bool isKeyPressed(EKey key) const;
    bool isKeyRepeated(EKey key) const;
    bool isKeyHeld(EKey key) const;
    bool isKeyReleased(EKey key) const;
    bool isKeyUnknow(EKey key) const;
    bool isKeyHeldSince(EKey key, float time) const;
    float getKeyHeldTime(EKey key) const;
    float getMousePositionX() const;
    float getMousePositionY() const;
    float getMouseDeltaX() const;
    float getMouseDeltaY() const;
    glm::vec2 getMousePosition() const;
    glm::vec2 getMouseDelta() const;

protected:
    float mousePositionX = 0.0f;
    float mousePositionY = 0.0f;
    float mousePositionLastX = 400.0f;
    float mousePositionLastY = 300.0f;
    float mouseScrollX = 0.0f;
    float mouseScrollY = 0.0f;

    std::unordered_map<EKey, InputInfo> keys;
    std::unordered_map<EMouseButton, InputInfo> mouseButtons;
    std::vector<KeyCallback> keyCallbacks;
    std::vector<MouseButtonCallback> mouseButtonCallbacks;
    std::vector<MousePositionCallback> mousePositionCallbacks;
    std::vector<MouseDeltaCallback> mouseDeltaCallbacks;
    std::vector<MouseScrollCallback> mouseScrollCallbacks;
};

#endif //A_INPUT_H