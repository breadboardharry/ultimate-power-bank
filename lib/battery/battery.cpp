#include "battery.h"

BAT::BAT(uint8_t _pin, uint8_t _cellNb, float _r1, float _r2): ADCPlus(_pin), cellNb(_cellNb), r1(_r1), r2(_r2) {
    prev_voltage = 0;
}

float BAT::getVoltage()
{
    // Current throught voltage divider with I=U/R
    float i = (ADCPlus::getVoltage() / r2);
    // Calculate voltage with U=RI
    float v = (r1 + r2) * i;

    if(v > prev_voltage - FILTERING_V && v < prev_voltage + FILTERING_V)
        v = prev_voltage;
    else prev_voltage = v;

    return v;
}

float BAT::getCellVoltage()
{
    return getVoltage()/cellNb;
}