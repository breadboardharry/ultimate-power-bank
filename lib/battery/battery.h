#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>
#include <math.h>
#include <adc.h>

#define R 1
#define K 1e3
#define M 1e6

class BAT: public ADCPlus {

    private:
        const float r1, r2;

    public:
        BAT ( uint8_t _pin, float _r1, float _r2 ): ADCPlus(_pin), r1(_r1), r2(_r2) {}

        float getVoltage();
};

#endif