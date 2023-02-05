#include "battery.h"

BAT::BAT(uint8_t _pin, uint8_t _cellNb, float _r1, float _r2): ADCPlus(_pin), cellNb(_cellNb), r1(_r1), r2(_r2) {
    
}

float BAT::getVoltage()
{
    // Current throught voltage divider with I=U/R
    float i = (ADCPlus::getVoltage() / r2);
    // Calculate voltage with U=RI
    return ((r1 + r2) * i);
}

float BAT::getCellVoltage()
{
    return getVoltage()/cellNb;
}