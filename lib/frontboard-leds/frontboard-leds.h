#ifndef FRONTBOARD_LEDS_H
#define FRONTBOARD_LEDS_H

#include <Arduino.h>
#include <FastLED.h>

#define DIN_PIN 6
#define NUM_LEDS 4
#define LED_TYPE SK6812
#define COLOR_ORDER GRB

#define FULL_CHARGE_COLOR CRGB(0, 32, 0)
#define NORMAL_CHARGE_COLOR CRGB(11, 21, 0)
#define MEDIUM_CHARGE_COLOR CRGB(20, 12, 0)
#define NORMAL_CHARGE_COLOR CRGB(11, 21, 0)
#define LOW_CHARGE_COLOR CRGB(31, 1, 0)
#define OUTPUT_COLOR CRGB(8, 12, 10)

class FRONTBOARD_LEDS
{
    private:
        CRGB leds[NUM_LEDS];

    public:
        FRONTBOARD_LEDS();
        FRONTBOARD_LEDS* fill(CRGB color);
        void batteryAlert(uint8_t reps);
        FRONTBOARD_LEDS* displayBatteryLevel(float vcell);
        FRONTBOARD_LEDS* displayOutputs(bool out1, bool out2);
        FRONTBOARD_LEDS* clear();
        void show();
};

#endif