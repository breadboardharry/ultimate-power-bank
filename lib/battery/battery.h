#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>
#include <math.h>
#include <adc.h>
#include <FastLED.h>

#define R 1
#define K 1e3
#define M 1e6

class BAT : public ADCPlus
{
    private:
        const float r1, r2;
        const uint8_t cellNb;

    public:
        BAT(uint8_t _pin, uint8_t _cellNb, float _r1, float _r2) : ADCPlus(_pin), cellNb(_cellNb), r1(_r1), r2(_r2) {}

        float getVoltage();
        float getCellVoltage();
};

#endif