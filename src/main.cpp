#include <Arduino.h>
#include <WifiCon.h>
// #include <AirTemp.h>
// #include <WaterTemp.h>
// #include <WiFi.h>
#include <ESPMqtt.h>
// #include <Ultrasonic.h>
#include <ArduinoJson.h>
#define LED 2

const char ssid[] = "myhotspot";
const char password[] = "nutert0405";
const char mqtt_clientId[] = "myesp32";
const char mqtt_server[] = "192.168.43.179";
const int port = 1883;
const char mqtt_username[] = "admin";
const char mqtt_password[] = "admin";
unsigned long time2 = 0;

char msg[100];
DynamicJsonDocument postMessage(2048);
// String jsonBody;

WifiCon wificon(ssid,password);
ESPMqtt MqttConnec(mqtt_clientId, mqtt_server ,port ,mqtt_username, mqtt_password);
// AirTemp Airtemp1(34,3.3,10000,4095);
// WaterTemp WaterTemp1(22);
// Ultrasonic Ultra1(5,18);

int list_out[] = {2,19,21,4};
const int sizelist = sizeof(list_out)/sizeof(list_out[0]);
char list_sub[sizelist][10] = {"light1","motor1","motor2","fog1"};


void setup()
{
    Serial.begin(115200);
    wificon.WifiInit();

    // Serial.print("Connecting to ");
    // Serial.println(ssid);

    // WiFi.begin(ssid, password);

    // while (WiFi.status() != WL_CONNECTED) {
        // delay(500);
    //     Serial.print(".");
    // }
    // randomSeed(micros());
    // Serial.println("");
    // Serial.println("WiFi connected");
    // Serial.println("IP address: ");
    // Serial.println(WiFi.localIP());

    
    MqttConnec.GetSub(sizelist,&list_sub[0],list_out);
    MqttConnec.initConn();
    
}

void loop()
{   
    // char TempC1[7];
    // char TempC2[7];
    wificon.WifiCheck();
    MqttConnec.CheckConn();

    // snprintf(TempC1,7,"%f",Airtemp1.CalTemp());
    // snprintf(TempC2,7,"%f",WaterTemp1.GetTemp());
    // MqttConnec.PubServ(1000,"room/temp1",TempC1);
    // MqttConnec.PubServ(1100,"room/temp2",TempC2);

    // String data = "{\"romm/temp1\":" + String(Airtemp1.CalTemp()) +
    //              ",\"room/temp2\":" + String(WaterTemp1.GetTemp()) +
    //              ",\"Humid\":" + String(100) + "}";
   
//    postMessage["room/temp1"] = String(Airtemp1.CalTemp());
//    postMessage["room/temp2"] = String(WaterTemp1.GetTemp());
//    postMessage["Humid"] = String(100);
//    postMessage["Level"] = String(Ultra1.GetRange());
//    serializeJson(postMessage, msg);
//    Serial.println(msg);
 
//    MqttConnec.PubServ(2000,"data",msg);
   
//    client.publish("@shadow/data/update", msg);



    // if(millis() - time2 > 1000)
    // {
    //     Serial.print("AirTemp : ");
    //     Serial.print(Airtemp1.CalTemp());
    //     Serial.print(" WaterTemp : ");
    //     Serial.println(WaterTemp1.GetTemp());

    //     time2 = millis();
    // }
}