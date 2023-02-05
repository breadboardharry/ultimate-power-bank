#include "frontboard-pb.h"

bool FRONTBOARD_PB::isPressed() {
    debug_println("\nisPressed");
    debug_println(this->pin);
    debug_println(!digitalRead(pin));
    return !digitalRead(pin);
}