#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>
#include <adc.h>

#define CUTOFF_VOLTAGE 3.15
#define STOP_VOLTAGE 3.2

class BAT : public ADCPlus
{
    private:
        const float r1, r2;
        const uint8_t cellNb;

    public:
        BAT(uint8_t _pin, uint8_t _cellNb, float _r1, float _r2);
        float getVoltage();
        float getCellVoltage();
};

#endif