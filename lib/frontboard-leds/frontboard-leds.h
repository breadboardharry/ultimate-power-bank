#ifndef FRONTBOARD_LEDS_H
#define FRONTBOARD_LEDS_H

#include <Arduino.h>
#include <FastLED.h>

#define DIN_PIN 6
#define NUM_LEDS 4
#define LED_TYPE SK6812
#define COLOR_ORDER GRB

class FRONTBOARD_LEDS
{
    private:
        const uint8_t pin;
        CRGB leds[];

    public:
        FRONTBOARD_LEDS(uint8_t _pin);
        FRONTBOARD_LEDS* fill(CRGB color);
        void batteryAlert(uint8_t reps);
        FRONTBOARD_LEDS* displayBatteryLevel(float vcell);
        FRONTBOARD_LEDS* displayOutputs(bool out1, bool out2);
        FRONTBOARD_LEDS* clear();
        void show();
};

#endif