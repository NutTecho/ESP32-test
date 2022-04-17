#include <AirTemp.h>

AirTemp::AirTemp(byte pin,double VCC,double R2,double adc_res)
{
    this->_pin = pin;
    this->_VCC = VCC;
    this->_R2 = R2;
    this->_adc_res = adc_res;
    pinMode(this->_pin,INPUT);
}

double AirTemp::AvgRead()
{
    double val = 0;
    for(int i = 0; i < 50; i++) 
    {
        val += analogRead(_pin);
        delay(10);
          
    }
    val = val / 50;
    return val;
}

double AirTemp::CalTemp()
{
    double adc_value,Rth,ln,tempC;
    adc_value = AvgRead();
    Rth = _R2 / ((_adc_res /adc_value )-1);
    ln = log(Rth / _R2);
    tempC = (1/((ln/BCO) + (1/Tx)));
    tempC = tempC - 273.15;
    return tempC;
}