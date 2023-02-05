#include "frontboard-leds.h"

FRONTBOARD_LEDS::FRONTBOARD_LEDS(uint8_t _pin) : pin(_pin)
{
    FastLED.addLeds<LED_TYPE, DIN_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    clear()->show();
}

FRONTBOARD_LEDS *FRONTBOARD_LEDS::fill(CRGB color)
{
    fill_solid(leds, NUM_LEDS, color);
    return this;
}

FRONTBOARD_LEDS *FRONTBOARD_LEDS::displayBatteryLevel(float vcell)
{
    static bool blink = false;
    clear()->show();

    if (vcell >= 3.9)
        fill_solid(leds, 4, CRGB(0, 32, 0));
    else if (vcell >= 3.7)
        fill_solid(leds, 3, CRGB(11, 21, 0));
    else if (vcell >= 3.45)
        fill_solid(leds, 2, CRGB(20, 12, 0));
    else if (vcell >= 3.3)
        fill_solid(leds, 1, CRGB(31, 1, 0));
    else
    {
        if (!blink)
            fill_solid(leds, 1, CRGB(31, 1, 0));
        blink = !blink;
    }

    return this;
}

FRONTBOARD_LEDS *FRONTBOARD_LEDS::displayOutputs(bool out1, bool out2)
{
    clear()->show();
    CRGB color = CRGB(8, 12, 10);
    leds[0] = out2 ? color : CRGB::Black;
    leds[1] = out1 ? color : CRGB::Black;
    leds[2] = out1 ? color : CRGB::Black;
    leds[3] = color;
    return this;
}

void FRONTBOARD_LEDS::batteryAlert(uint8_t reps)
{
    clear()->show();
    for (uint8_t i = 0; i < 2*reps; i++)
    {
        leds[0] = i%2==0 ? CRGB(31, 1, 0) : CRGB::Black;
        show();
        delay(350);
    }
}

FRONTBOARD_LEDS *FRONTBOARD_LEDS::clear()
{
    fill(CRGB::Black);
    return this;
}

void FRONTBOARD_LEDS::show()
{
    FastLED.show();
}