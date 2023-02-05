#include "outputs.h"

OUTPUTS::OUTPUTS(uint8_t _out1_pin, uint8_t _out2_pin): out1_pin(_out1_pin), out2_pin(_out2_pin) {
    pinMode(out1_pin, OUTPUT);
    pinMode(out2_pin, OUTPUT);
    disable();
}

void OUTPUTS::handle(bool show) {
  static uint8_t cycle = 0;

  if (show)
  {
    cycle = (cycle + 1) % 4;

    en_out1 = cycle == 2 || cycle == 3;
    en_out2 = cycle == 1 || cycle == 3;

    digitalWrite(out1_pin, en_out1);
    digitalWrite(out2_pin, en_out2);
  }
}

void OUTPUTS::disable() {
    digitalWrite(out1_pin, LOW);
    digitalWrite(out2_pin, LOW);
}

