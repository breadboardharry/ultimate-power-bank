#include <Arduino.h>
#include <FastLED.h>
#include "battery.h"
#include "frontboard-leds.h"
#include "frontboard-pb.h"
#include "debug.h"

#define VBAT_PIN 0
#define EN_OUT1_PIN 4
#define EN_OUT2_PIN 1
#define PB_PIN 5
#define DIN_PIN 6
#define LED_PIN 7
#define SCL_PIN 18
#define SDA_PIN 19
#define INT_PIN 3

#define PB !digitalRead(PB_PIN)

BAT* battery;
FRONTBOARD_LEDS* leds;
FRONTBOARD_PB* pb;

FRONTBOARD_PB* pb;

void testProgram();

void setup() {
  pb = new FRONTBOARD_PB(PB_PIN);
  pinMode(EN_OUT1_PIN, OUTPUT);
  pinMode(EN_OUT2_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  
  // esp_deep_sleep_enable_gpio_wakeup(0x20, ESP_GPIO_WAKEUP_GPIO_LOW);
  // debug_println("Going to sleep now");
  // esp_deep_sleep_start();
  // debug_println("Should not be printed");
}

void loop() {
  while(true) {
    digitalWrite(LED_PIN, pb->isPressed());
  }
  testProgram();
}

void testProgram() {
  while(true) {
    debug_println(battery->getVoltage());

    leds->displayBatteryLevel(battery->getCellVoltage());
    leds->show();
    delay(1000);
    leds->clear();
    leds->show();

    delay(300);
  }
}