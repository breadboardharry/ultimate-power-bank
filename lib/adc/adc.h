#ifndef ADC_H
#define ADC_H

#include <Arduino.h>
#include <math.h>

class ADCPlus {

    protected:
        const uint8_t pin;
        float vref, quantum;

    public:
        ADCPlus ( uint8_t _pin, uint8_t _res = 12, float _vref = 3 ): pin (_pin) {
            setVref(_vref);
            setResolution(_res);
        }

        void setVref ( float _voltage ) {
            vref = _voltage;
        }

        void setResolution ( uint8_t _res ) {
            quantum = vref / pow(2, _res);
        }

        float getVoltage () {
            return analogRead(pin) * quantum;
        }
};

#endif