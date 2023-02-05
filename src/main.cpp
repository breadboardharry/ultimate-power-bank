#include <Arduino.h>
#include <FastLED.h>
#include <Wire.h>
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

#define BP_MASK 0x20

#define led_on digitalWrite(LED_PIN, LOW)
#define led_off digitalWrite(LED_PIN, HIGH)

#define SECOND_CONSTANT 1e3
#define HOUR_CONSTANT 3.6e6
#define SAFETY_SLEEP_TIMEOUT 2 * HOUR_CONSTANT
#define SLEEP_TIMEOUT 30 * SECOND_CONSTANT

#define CUTOFF_VOLTAGE 3.2

BAT *battery;
FRONTBOARD_LEDS *leds;
FRONTBOARD_PB *pb;

void turnOff();
void sleep();
void handleOutputs();

bool en_out1 = false, en_out2 = false;
float vbat = 0;

void setup()
{
  battery = new BAT(VBAT_PIN, 5, 3000, 470);
  leds = new FRONTBOARD_LEDS(DIN_PIN);
  pb = new FRONTBOARD_PB(PB_PIN);

  pinMode(EN_OUT1_PIN, OUTPUT);
  pinMode(EN_OUT2_PIN, OUTPUT);
  digitalWrite(EN_OUT1_PIN, en_out1);
  digitalWrite(EN_OUT2_PIN, en_out2);
  pinMode(LED_PIN, OUTPUT);
  led_on;

  vbat = battery->getCellVoltage();
  if(vbat <= CUTOFF_VOLTAGE)
  {
    leds->batteryAlert(3);
    turnOff();
  }
  leds->displayBatteryLevel(vbat)->show();

  while (pb->isPressed());
}

bool pb_long_press_en = true;
uint32_t sleep_millis = 0;
uint32_t leds_millis = 0;
uint32_t pb_millis = 0;
bool show_outputs = false;
uint32_t outputs_millis = 0;
uint8_t bat_cycle = 0;

void loop()
{
  if (millis() >= SAFETY_SLEEP_TIMEOUT)
  {
    turnOff();
  }

  if (show_outputs && millis() - outputs_millis >= 4000)
  {
    show_outputs = false;
    sleep_millis = millis();
  }

  if (!en_out1 && !en_out2 && millis() - sleep_millis >= SLEEP_TIMEOUT)
  {
    turnOff();
  }

  if (!show_outputs && millis() - leds_millis >= 1000)
  {
    if (!bat_cycle)
      vbat = battery->getCellVoltage();
    if (vbat <= CUTOFF_VOLTAGE)
      turnOff();
    leds->displayBatteryLevel(vbat)->show();
    bat_cycle = (bat_cycle + 1) % 5;
    leds_millis = millis();
  }

  if (pb->isPressed())
  {
    if (!pb_millis)
      pb_millis = millis();
    else
    {
      if (millis() - pb_millis >= 3000)
      {
        turnOff();
      }
    }
  }
  else if (pb_millis)
  {
    uint32_t pb_delta_millis = millis() - pb_millis;
    if (pb_delta_millis <= 2000)
    {
      handleOutputs();
      show_outputs = true;
      outputs_millis = millis();
      sleep_millis = millis();
    }
    pb_millis = 0;
  }
}

void handleOutputs()
{
  static uint8_t cycle = 0;

  if (show_outputs)
  {
    cycle = (cycle + 1) % 4;

    en_out1 = cycle == 2 || cycle == 3;
    en_out2 = cycle == 1 || cycle == 3;

    digitalWrite(EN_OUT1_PIN, en_out1);
    digitalWrite(EN_OUT2_PIN, en_out2);
  }

  leds->displayOutputs(en_out1, en_out2)->show();
}

void turnOff()
{
  leds->clear()->show();
  digitalWrite(EN_OUT1_PIN, LOW);
  digitalWrite(EN_OUT2_PIN, LOW);
  led_off;

  while (pb->isPressed())
    ;

  sleep();
}

void sleep()
{
  esp_deep_sleep_enable_gpio_wakeup(BP_MASK, ESP_GPIO_WAKEUP_GPIO_LOW);
  debug_println("Going to sleep now");
  esp_deep_sleep_start();
  debug_println("Should not be printed");
}