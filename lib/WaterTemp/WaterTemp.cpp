#include <WaterTemp.h>

WaterTemp :: WaterTemp(uint8_t pin)
 : _pin(pin),wire(_pin),sensor(&wire)
{
     if (sensor.begin() == false)
    {
        Serial.println("ERROR: No device found");
        while (!sensor.begin()); // wait until device comes available.
    }

    sensor.setResolution(12);
    sensor.setConfig(DS18B20_CRC);  // or 1
    sensor.requestTemperatures();
}

double WaterTemp :: GetTemp()
{
    
    sensor.requestTemperatures();
    // wait for data AND detect disconnect
    uint32_t timeout = millis();
    while (!sensor.isConversionComplete())
    {
        if (millis() - timeout >= 800) // check for timeout
        {
        Serial.println("ERROR: timeout or disconnect");
        break;
        }
    }

    float t = sensor.getTempC();
    return t;
    
}