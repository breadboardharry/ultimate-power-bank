#include "battery.h"

float BAT::getVoltage () {
    // Current throught voltage divider with I=U/R
    float i = (ADCPlus::getVoltage()/r2);
    // Calculate voltage with U=RI
    return ((r1+r2) * i);
}