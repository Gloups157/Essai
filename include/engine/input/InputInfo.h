#ifndef INPUT_INFO_H
#define INPUT_INFO_H

#include "EInputState.h"

struct InputInfo {
    EInputState state;
    float heldTime;

    InputInfo(): state(EInputState::IDLE), heldTime(0.0f) {}

    void update(EInputState newState) {
        switch (newState) {
            case EInputState::IDLE:
                state = EInputState::IDLE;
                break;
            case EInputState::PRESSED:
                if (state == EInputState::PRESSED) {
                    state = EInputState::HELD;
                    //heldTime += Time::getDeltaTime();
                }
                else if (state == EInputState::IDLE) {
                    state = EInputState::PRESSED;
                }
                break;
            case EInputState::REPEATED:
                state = EInputState::REPEATED;
                break;
            case EInputState::HELD:
                state = EInputState::HELD;
                //heldTime += Time::getDeltaTime();
                break;
            case EInputState::RELEASED:
                if (state == EInputState::RELEASED) {
                    state = EInputState::IDLE;
                    heldTime = 0.0f;
                }
                break;
            default:
                state = EInputState::UNKNOWN;
                heldTime = 0.0f;
                break;
        }
    }
};

#endif //INPUT_INFO_H