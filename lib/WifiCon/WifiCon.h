#ifndef WifiCon_H
#define WifiCon_H

#include <WiFi.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class WifiCon
{
private:
    const char *_ssid;
    const char *_passwd;
    HTTPClient client;
    unsigned long previous_time = 0;
    unsigned long delay = 20000;
    long lastMsg = 0;
    
public:
    WifiCon(const char *ssid,const char *passwd);
    void WifiInit();
    void GetAPI();
    void PutAPI();
    void WifiCheck();
    
};
#endif