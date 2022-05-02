#include "WifiCon.h"

WifiCon :: WifiCon(const char *ssid,const char *passwd)
{
    this->_ssid = ssid;
    this->_passwd = passwd;
}
void WifiCon :: WiFiEvent(WiFiEvent_t event)
{
    Serial.printf("[WiFi-event] event: %d\n", event);

    switch (event) {
        case ARDUINO_EVENT_WIFI_READY: 
            Serial.println("WiFi interface ready");
            break;
        case ARDUINO_EVENT_WIFI_SCAN_DONE:
            Serial.println("Completed scan for access points");
            break;
        case ARDUINO_EVENT_WIFI_STA_START:
            Serial.println("WiFi client started");
            break;
        case ARDUINO_EVENT_WIFI_STA_STOP:
            Serial.println("WiFi clients stopped");
            break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            Serial.println("Connected to access point");
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            Serial.println("Disconnected from WiFi access point");
            break;
        case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
            Serial.println("Authentication mode of access point has changed");
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            Serial.print("Obtained IP address: ");
            Serial.println(WiFi.localIP());
            break;
        case ARDUINO_EVENT_WIFI_STA_LOST_IP:
            Serial.println("Lost IP address and IP address is reset to 0");
            break;
        case ARDUINO_EVENT_WPS_ER_SUCCESS:
            Serial.println("WiFi Protected Setup (WPS): succeeded in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_FAILED:
            Serial.println("WiFi Protected Setup (WPS): failed in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_TIMEOUT:
            Serial.println("WiFi Protected Setup (WPS): timeout in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_PIN:
            Serial.println("WiFi Protected Setup (WPS): pin code in enrollee mode");
            break;
        case ARDUINO_EVENT_WIFI_AP_START:
            Serial.println("WiFi access point started");
            break;
        case ARDUINO_EVENT_WIFI_AP_STOP:
            Serial.println("WiFi access point  stopped");
            break;
        case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
            Serial.println("Client connected");
            break;
        case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
            Serial.println("Client disconnected");
            break;
        case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
            Serial.println("Assigned IP address to client");
            break;
        case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED:
            Serial.println("Received probe request");
            break;
        case ARDUINO_EVENT_WIFI_AP_GOT_IP6:
            Serial.println("AP IPv6 is preferred");
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP6:
            Serial.println("STA IPv6 is preferred");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP6:
            Serial.println("Ethernet IPv6 is preferred");
            break;
        case ARDUINO_EVENT_ETH_START:
            Serial.println("Ethernet started");
            break;
        case ARDUINO_EVENT_ETH_STOP:
            Serial.println("Ethernet stopped");
            break;
        case ARDUINO_EVENT_ETH_CONNECTED:
            Serial.println("Ethernet connected");
            break;
        case ARDUINO_EVENT_ETH_DISCONNECTED:
            Serial.println("Ethernet disconnected");
            break;
        case ARDUINO_EVENT_ETH_GOT_IP:
            Serial.println("Obtained IP address");
            break;
        default: break;
    }
}

void WifiCon :: Wifi_connected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println("Successfully connected to Access Point");
}

void WifiCon :: Get_IPAddress(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println("WIFI is connected!");
  Serial.println("IP address: ");
  Serial.println(IPAddress(info.got_ip.ip_info.ip.addr));
  Serial.println(WiFi.localIP());
}

void WifiCon :: Wifi_disconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println("Disconnected from WIFI access point");
  Serial.print("WiFi lost connection. Reason: ");
  // Serial.println(info.disconnected.reason);
  Serial.println("Reconnecting...");
  // WiFi.begin(_ssid, _passwd);
}

void WifiCon :: WifiInit()
{
    WiFi.disconnect(true);
    
    WiFi.onEvent(WiFiEvent);
    WiFi.onEvent(Wifi_connected,WiFiEvent_t :: ARDUINO_EVENT_WIFI_STA_CONNECTED);
    WiFi.onEvent(Get_IPAddress, WiFiEvent_t :: ARDUINO_EVENT_WIFI_STA_GOT_IP);
    WiFi.onEvent(Wifi_disconnected, WiFiEvent_t :: ARDUINO_EVENT_WIFI_STA_DISCONNECTED); 

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