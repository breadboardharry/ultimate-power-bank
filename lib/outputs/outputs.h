#ifndef OUTPUTS_H
#define OUTPUTS_H

#include <Arduino.h>

class OUTPUTS
{
    private:
        const uint8_t out1_pin, out2_pin;
        bool show_outputs = false;

    public:
        OUTPUTS(uint8_t _out1_pin, uint8_t _out2_pin);
        void handle(bool show);
        void disable();

        bool en_out1 = false, en_out2 = false;
};

#endif