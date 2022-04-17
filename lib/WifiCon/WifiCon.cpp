#include "WifiCon.h"

WifiCon :: WifiCon(const char *ssid,const char *passwd)
{
    this->_ssid = ssid;
    this->_passwd = passwd;
}
void WifiCon :: WifiInit()
{
    Serial.print("Connecting to ");
    Serial.println(_ssid);

    WiFi.begin(_ssid, _passwd);

    while (WiFi.status() != WL_CONNECTED) {
      long now = millis();
      if (now - lastMsg > 500)
       {
        lastMsg = now;
        Serial.print(".");
       }
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void WifiCon ::  WifiCheck()
{
    //unsigned long current_time = millis(); 

  // checking for WIFI connection
    if(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(millis());
        Serial.println("Reconnecting to WIFI network");
        WiFi.disconnect();
        WiFi.reconnect();
        //this->previous_time = current_time;
    }
    
}
void WifiCon :: GetAPI()
{
    if(WiFi.status() == WL_CONNECTED)
    {
        client.begin("");
        int httpCode = client.GET();
        if( httpCode > 0)
        {
            String payload = client.getString();
            Serial.println("\nStatuscode : " + String(httpCode));
            Serial.println(payload);
            char json[500];

            // decolation JSON before convert to char array
            payload.replace(" ","");
            payload.replace("\n","");
            payload.trim();
            payload.remove(0,1);
            
            payload.toCharArray(json,sizeof(json));
            StaticJsonDocument<200> doc;
            deserializeJson(doc,json);

            client.end();
        }
       
    }
    else
    {
        Serial.println("Connection lost");
    }
}