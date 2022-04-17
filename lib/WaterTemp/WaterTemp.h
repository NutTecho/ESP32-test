#ifndef WaterTemp_H
#define WaterTemp_H

#include <OneWire.h>
#include <DS18B20.h>
#include <Arduino.h>

class WaterTemp
{
    private:
        uint8_t _pin;
        OneWire wire;
        DS18B20 sensor;


    public:
        WaterTemp(uint8_t pin);
        double GetTemp();
};

#endif

