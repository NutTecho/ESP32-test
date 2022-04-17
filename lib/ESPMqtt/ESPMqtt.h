#ifndef ESPMqtt_H
#define ESPMqtt_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

class ESPMqtt
{
private:
    WiFiClient espClient;
    PubSubClient client;
    const char* mqtt_clientId;
    const char* mqtt_server;
    const char* mqtt_username;
    const char* mqtt_password;
    char (*list_topic)[10];
    int *list_pin;
    int sizelist;
    int port;
    long lastMsg = 0;
    
    
public:
    ESPMqtt(const char* _mqtt_clientId,
            const char* _mqtt_server, 
            int _port,
            const char* _mqtt_username,
            const char* _mqtt_password);

    void initConn();
    void ReConnec();
    void CheckConn();
    void GetSub(int sizelist,char (*topic)[10],int *pin);
    void SubServ();
    void PubServ(int time_delay,char *topic,char *value);
    void SetOutPut(char *topic,char *message );
    void callback(char* topic, byte* payload, unsigned int length);


};
#endif