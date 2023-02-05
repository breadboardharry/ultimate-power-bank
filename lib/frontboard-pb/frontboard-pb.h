#ifndef FRONTBOARD_PB_H
#define FRONTBOARD_PB_H

#include <Arduino.h>
#include "debug.h"

class FRONTBOARD_PB
{
    private:
        const uint8_t pin;

    public:
        FRONTBOARD_PB(uint8_t _pin): pin(_pin) {};
        bool isPressed();
};

#endif