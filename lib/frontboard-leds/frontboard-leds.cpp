#include "frontboard-leds.h"

FRONTBOARD_LEDS::FRONTBOARD_LEDS(uint8_t _pin) : pin(_pin)
{
    FastLED.addLeds<LED_TYPE, DIN_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    clear();
}

void FRONTBOARD_LEDS::fill(CRGB color)
{
    fill_solid(leds, NUM_LEDS, color);
}

void FRONTBOARD_LEDS::displayBatteryLevel(float vcell)
{
    if (vcell >= 3.9)
        fill_solid(leds, 4, CRGB(0, 32, 0));
    else if (vcell >= 3.7)
        fill_solid(leds, 3, CRGB(11, 21, 0));
    else if (vcell >= 3.35)
        fill_solid(leds, 2, CRGB(20, 12, 0));
    else
        fill_solid(leds, 1, CRGB(31, 1, 0));
}

void FRONTBOARD_LEDS::clear()
{
    fill(CRGB::Black);
}

void FRONTBOARD_LEDS::show()
{
    FastLED.show();
}