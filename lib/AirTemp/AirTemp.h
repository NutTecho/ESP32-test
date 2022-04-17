#ifndef AirTemp_H
#define AirTemp_H
#include <Arduino.h>

class AirTemp
{
    private:
        byte _pin;
        double _VCC;           // NodeMCU on board 3.3v vcc
        double _R2;            // 10k ohm series resistor
        double _adc_res;       // 10-bit adc
        unsigned long time1 = 0;
        const int BCO = 3977;
        const double Tx = 25.0 + 273.15;  

    public:
        AirTemp(byte pin,double VCC,double R2,double adc_res);
        double AvgRead();
        double CalTemp();


};
#endif