#include "../../../../include/core/utilities/helpers/AActivable.h"

void Core::AActivable::enable() {
    active = true;
}

void Core::AActivable::disable() {
    active = false;
}

void Core::AActivable::toggle() {
    active = !active;
}

bool Core::AActivable::isActive() const {
    return active;
}
