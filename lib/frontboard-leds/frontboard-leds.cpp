#include "frontboard-leds.h"

FRONTBOARD_LEDS::FRONTBOARD_LEDS()
{
    clear();
    FastLED.addLeds<LED_TYPE, DIN_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    show();
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

    if (vcell >= 3.9) fill_solid(leds, 4, FULL_CHARGE_COLOR);
    else if (vcell >= 3.7) fill_solid(leds, 3, NORMAL_CHARGE_COLOR);
    else if (vcell >= 3.45) fill_solid(leds, 2, MEDIUM_CHARGE_COLOR);
    else if (vcell >= 3.3) fill_solid(leds, 1, LOW_CHARGE_COLOR);
    else
    {
        if (!blink) fill_solid(leds, 1, LOW_CHARGE_COLOR);
        blink = !blink;
    }

    return this;
}

FRONTBOARD_LEDS *FRONTBOARD_LEDS::displayOutputs(bool out1, bool out2)
{
    clear()->show();
    leds[0] = out2 ? OUTPUT_COLOR : CRGB::Black;
    leds[1] = out1 ? OUTPUT_COLOR : CRGB::Black;
    leds[2] = out1 ? OUTPUT_COLOR : CRGB::Black;
    leds[3] = OUTPUT_COLOR;
    return this;
}

void FRONTBOARD_LEDS::batteryAlert(uint8_t reps)
{
    clear()->show();
    for (uint8_t i = 0; i < 2*reps; i++)
    {
        leds[0] = i%2==0 ? LOW_CHARGE_COLOR : CRGB::Black;
        show();
        delay(300);
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