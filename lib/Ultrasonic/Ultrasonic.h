#ifndef Ultrasonic_H
#define Ultrasonic_H

#include <Arduino.h>
class Ultrasonic
{
private:
    uint8_t _pingpin;
    uint8_t _inpin;
public:
    Ultrasonic(uint8_t pinpin,uint8_t inpin);
    long GetRange();

};

#endif
