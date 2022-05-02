#ifndef WifiCon_H
#define WifiCon_H

#include <WiFi.h>
// #include <WiFiType.h>
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
    static void WiFiEvent(WiFiEvent_t event);
    static void Wifi_connected(WiFiEvent_t event, WiFiEventInfo_t info);
    static void Wifi_disconnected(WiFiEvent_t event, WiFiEventInfo_t info);
    static void Get_IPAddress(WiFiEvent_t event, WiFiEventInfo_t info);
    
public:
    WifiCon(const char *ssid,const char *passwd);
    void WifiInit();
    void GetAPI();
    void PutAPI();
    void WifiCheck();
    
};
#endif