#include <Arduino.h>
#include <FastLED.h>
#include <Wire.h>
#include "battery.h"
#include "frontboard-leds.h"
#include "frontboard-pb.h"
#include "debug.h"
#include "outputs.h"

#define VBAT_PIN 0
#define EN_OUT1_PIN 4
#define EN_OUT2_PIN 1
#define PB_PIN 5
#define DIN_PIN 6
#define LED_PIN 7
#define SCL_PIN 18
#define SDA_PIN 19
#define INT_PIN 3

#define BP_MASK 0x20

#define led_on digitalWrite(LED_PIN, LOW)
#define led_off digitalWrite(LED_PIN, HIGH)

#define SECOND_CONSTANT 1e3
#define HOUR_CONSTANT 3.6e6
#define SAFETY_SLEEP_TIMEOUT 2 * HOUR_CONSTANT
#define SLEEP_TIMEOUT 30 * SECOND_CONSTANT

BAT *battery;
FRONTBOARD_LEDS *leds;
FRONTBOARD_PB *pb;
OUTPUTS *outputs;

void turnOff();
void sleep();

float vbat = 0;
uint32_t sleep_millis = 0;
uint32_t leds_millis = 0;
uint32_t pb_millis = 0;
bool show_outputs = false;
uint32_t outputs_millis = 0;
uint8_t bat_cycle = 0;

void setup() {
  battery = new BAT(VBAT_PIN, 5, 3000, 470);

  vbat = battery->getCellVoltage();
  if (vbat <= CUTOFF_VOLTAGE) turnOff();

  leds = new FRONTBOARD_LEDS();

  if (vbat <= STOP_VOLTAGE)
  {
    leds->batteryAlert(3);
    turnOff();
  }

  pb = new FRONTBOARD_PB(PB_PIN);
  outputs = new OUTPUTS(EN_OUT1_PIN, EN_OUT2_PIN);

  leds->displayBatteryLevel(vbat)->show();

  while (pb->isPressed());
}

void loop() {
  // SAFETY SHUTDOWN TIMEOUT
  if (millis() >= SAFETY_SLEEP_TIMEOUT) turnOff();

  // OUTPUT MENU TIMER
  if (show_outputs && millis() - outputs_millis >= 4000)
  {
    show_outputs = false;
    sleep_millis = millis();
  }

  // NO ACTION SHUTDOWN TIMER
  if (!outputs->en_out1 && !outputs->en_out2 && millis() - sleep_millis >= SLEEP_TIMEOUT) turnOff();

  // BATTERY LEVEL TIMER
  if (!show_outputs && millis() - leds_millis >= 1000)
  {
    if (!bat_cycle) vbat = battery->getCellVoltage();
    if (vbat <= STOP_VOLTAGE) turnOff();
    leds->displayBatteryLevel(vbat)->show();
    bat_cycle = (bat_cycle + 1) % 5;
    leds_millis = millis();
  }

  // PUSHBUTTON
  if (pb->isPressed())
  {
    if (!pb_millis) pb_millis = millis();
    // SHUTDOWN ON LONG PRESS 
    else if (millis() - pb_millis >= 3000) turnOff();
  }
  // WHEN RELEASED
  else if (pb_millis)
  {
    // CALCULATE PRESS TIME
    uint32_t pb_delta_millis = millis() - pb_millis;
    // SHORT PRESS
    if (pb_delta_millis <= 2000)
    {
      // CONFIGURE OUTPUTS
      outputs->handle(show_outputs);
      leds->displayOutputs(outputs->en_out1, outputs->en_out2)->show();
      show_outputs = true;
      outputs_millis = millis();
      sleep_millis = millis();
    }
    // RESET
    pb_millis = 0;
  }
}

void turnOff() {
  leds->clear()->show();
  outputs->disable();

  while (pb->isPressed());

  sleep();
}

void sleep() {
  esp_deep_sleep_enable_gpio_wakeup(BP_MASK, ESP_GPIO_WAKEUP_GPIO_LOW);
  esp_deep_sleep_start();
  debug_println("Should not be printed");
}