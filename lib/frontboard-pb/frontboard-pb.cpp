#include "frontboard-pb.h"

FRONTBOARD_PB::FRONTBOARD_PB(uint8_t _pin): pin(_pin) {};

bool FRONTBOARD_PB::isPressed() {
    return !digitalRead(pin);
}