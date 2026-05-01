#include "engine/input/AInput.h"

AInput::AInput() {
    for (int i = static_cast<int>(EKey::A); i <= static_cast<int>(EKey::UNKNOWN); ++i) {
        auto key = static_cast<EKey>(i);
        keys[key] = InputInfo();
    }
    for (int i = static_cast<int>(EMouseButton::LEFT); i <= static_cast<int>(EMouseButton::RIGHT); ++i) {
        auto mouseButton = static_cast<EMouseButton>(i);
        mouseButtons[mouseButton] = InputInfo();
    }
}

void AInput::registerKeyCallback(const KeyCallback &callback) {
    keyCallbacks.push_back(callback);
}

void AInput::registerMouseButtonCallback(const MouseButtonCallback &callback) {
    mouseButtonCallbacks.push_back(callback);
}

void AInput::registerMousePositionCallback(const MousePositionCallback &callback) {
    mousePositionCallbacks.push_back(callback);
}

void AInput::registerMouseDeltaCallback(const MouseDeltaCallback &callback) {
    mouseDeltaCallbacks.push_back(callback);
}

void AInput::registerMouseScrollCallback(const MouseScrollCallback &callback) {
    mouseScrollCallbacks.push_back(callback);
}

bool AInput::isKeyIdle(const EKey key) const {
    return keys.find(key)->second.state == EInputState::IDLE;
}

bool AInput::isKeyPressed(const EKey key) const {
    return keys.find(key)->second.state == EInputState::PRESSED;
}

bool AInput::isKeyRepeated(const EKey key) const {
    return keys.find(key)->second.state == EInputState::REPEATED;
}

bool AInput::isKeyHeld(const EKey key) const {
    return keys.find(key)->second.state == EInputState::HELD;
}

bool AInput::isKeyReleased(const EKey key) const {
    return keys.find(key)->second.state == EInputState::RELEASED;
}

bool AInput::isKeyUnknow(const EKey key) const {
    return keys.find(key)->second.state == EInputState::UNKNOWN;
}

bool AInput::isKeyHeldSince(const EKey key, const float time) const {
    return keys.find(key)->second.heldTime == time;
}

float AInput::getKeyHeldTime(const EKey key) const {
    return keys.find(key)->second.heldTime;
}

float AInput::getMousePositionX() const {
    return mousePositionX;
}

float AInput::getMousePositionY() const {
    return mousePositionY;
}

float AInput::getMouseDeltaX() const {
    return mousePositionLastX - mousePositionX;
}

float AInput::getMouseDeltaY() const {
    return mousePositionLastY - mousePositionY;
}

glm::vec2 AInput::getMousePosition() const {
    return {mousePositionX, mousePositionY};
}

glm::vec2 AInput::getMouseDelta() const {
    return {getMouseDeltaX(), getMouseDeltaY()};
}
