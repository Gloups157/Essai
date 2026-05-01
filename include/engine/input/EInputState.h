#ifndef E_INPUT_STATE_H
#define E_INPUT_STATE_H

enum class EInputState {
    IDLE,
    PRESSED,
    REPEATED,
    HELD,
    RELEASED,
    UNKNOWN
};

#endif //E_INPUT_STATE_H