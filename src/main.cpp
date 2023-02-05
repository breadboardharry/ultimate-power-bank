#include <Arduino.h>
#include <FastLED.h>
#include "battery.h"

#define VBAT_PIN 0
#define EN_OUT1_PIN 4
#define EN_OUT2_PIN 1
#define PB_PIN 5
#define DIN_PIN 6
#define LED_PIN 7
#define SCL_PIN 18
#define SDA_PIN 19
#define INT_PIN 3

#define NUM_LEDS 4
#define LED_TYPE SK6812
#define BRIGHTNESS 20
#define UPDATES_PER_SECOND 100
#define COLOR_ORDER GRB

#define SW !digitalRead(SW_PIN)

FRONTBOARD_PB* pb;

BAT battery(VBAT_PIN, 3000, 470);

void testProgram();

void setup() {
  pb = new FRONTBOARD_PB(PB_PIN);
  pinMode(EN_OUT1_PIN, OUTPUT);
  pinMode(EN_OUT2_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  pinMode(DIN_PIN, OUTPUT);

  delay(100);

  Serial.begin(9600);
  Serial.println("Setup");
  
  FastLED.addLeds<LED_TYPE, DIN_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness( BRIGHTNESS );
  fill_solid( leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  
  delay(100);

  fill_solid( leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(200);

  fill_solid( leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  esp_deep_sleep_enable_gpio_wakeup(0x20, ESP_GPIO_WAKEUP_GPIO_LOW);
  Serial.println("Going to sleep now");
  esp_deep_sleep_start();
  Serial.println("Should not be printed");
}

void loop() {
  while(true) {
    digitalWrite(LED_PIN, pb->isPressed());
  }
  testProgram();
}

void testProgram() {
  Serial.println(battery.getVoltage());

  digitalWrite(LED_PIN, LOW);

  if(SW) {
    digitalWrite(LED_PIN, HIGH);
    fill_solid( leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
    delay(200);

    fill_solid( leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
    delay(200);

    fill_solid( leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();
    delay(200);

    fill_solid( leds, NUM_LEDS, CRGB::Black);
    FastLED.show();

    digitalWrite(EN_OUT1_PIN, HIGH);
    delay(1000);
    digitalWrite(EN_OUT2_PIN, HIGH);
    delay(5000);
    digitalWrite(EN_OUT1_PIN, LOW);
    delay(1000);
    digitalWrite(EN_OUT2_PIN, LOW);
  }

  delay(300);
}