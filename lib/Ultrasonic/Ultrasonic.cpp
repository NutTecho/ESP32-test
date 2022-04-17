#include <Ultrasonic.h>


Ultrasonic :: Ultrasonic(uint8_t pingpin,uint8_t inpin)
{
    this->_pingpin = pingpin;
    this->_inpin = inpin;
    pinMode(_pingpin,OUTPUT);
}

long microsecondsToCentimeters(long microseconds)
{
// ความเร็วเสียงในอากาศประมาณ 340 เมตร/วินาที หรือ 29 ไมโครวินาที/เซนติเมตร
// ระยะทางที่ส่งเสียงออกไปจนเสียงสะท้อนกลับมาสามารถใช้หาระยะทางของวัตถุได้
// เวลาที่ใช้คือ ระยะทางไปกลับ ดังนั้นระยะทางคือ ครึ่งหนึ่งของที่วัดได้
return microseconds / 29 / 2;
}

long Ultrasonic :: GetRange()
{
    long duration, cm;
    pinMode(_pingpin, OUTPUT);
    digitalWrite(_pingpin, LOW);
    delayMicroseconds(2);
    digitalWrite(_pingpin, HIGH);
    delayMicroseconds(5);
    digitalWrite(_pingpin, LOW);
    pinMode(_inpin, INPUT);
    duration = pulseIn(_inpin, HIGH);
    cm = microsecondsToCentimeters(duration);
    // Serial.print(cm);
    // Serial.print("cm");
    // Serial.println();
    return cm;
}