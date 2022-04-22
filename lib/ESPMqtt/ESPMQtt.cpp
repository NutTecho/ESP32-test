#include <ESPMqtt.h>


ESPMqtt::ESPMqtt(
            const char* _mqtt_clientId,
            const char* _mqtt_server, 
            int _port,
            const char* _mqtt_username,
            const char* _mqtt_password)
            :client(espClient)
{
      mqtt_clientId = _mqtt_clientId;
      mqtt_server = _mqtt_server;
      mqtt_username = _mqtt_username;
      mqtt_password = _mqtt_password;
      port = _port;

}

void ESPMqtt::initConn()
{
    client.setServer(mqtt_server, port);
    client.setCallback([this] (char* topic, byte* payload, unsigned int length) { this->callback(topic, payload, length); });
    client.connect(mqtt_clientId,mqtt_username,mqtt_password);
    if (client.connect(mqtt_clientId,mqtt_username,mqtt_password)) 
    {
      Serial.println("MQTT connected");
      SubServ();
    } 
    else
    {
      Serial.println("MQTT Reconect");
      ReConnec();
    }
}
void ESPMqtt :: GetSub(int sizelist,char (*topic)[10],int* pin)
{
    this->list_pin = pin;
    this->list_topic = topic;
    this->sizelist = sizelist;

}
void ESPMqtt::ReConnec()
{
      Serial.print("Attempting MQTT connection...");
       if (client.connect(mqtt_clientId,mqtt_username,mqtt_password)) 
       {
        Serial.println("MQTT connected");
        SubServ();
       } 
       else
        {
          Serial.print("failed, rc=");
          Serial.print(client.state());
          Serial.println(" try again in 5 seconds");

        }
}
void ESPMqtt:: SubServ()
{
  Serial.println("Initialize subscribe...");
  for (int i = 0; i < this->sizelist ; i++)
  {
      Serial.println(this->list_topic[i]);
      pinMode(this->list_pin[i],OUTPUT);
      client.subscribe(this->list_topic[i]);
      
  }
}
void ESPMqtt::PubServ(int time_delay,char *topic,char *value)
{
      long now = millis();
      if (now - lastMsg > time_delay) {
        lastMsg = now;
        client.publish(topic,value);
      }
}
void ESPMqtt :: CheckConn()
{
    while (!client.connected()) {
      ReConnec();
    }
    client.loop();
}
void ESPMqtt :: SetOutPut(char *topic,char *message)
{
  for (int i = 0; i < this->sizelist ; i++)
  {
    // Serial.println(this->list_topic[i]);
    if(strcmp(topic,list_topic[i]) == 0) 
    {
      if(strcmp(message,"on") == 0)
      {
        digitalWrite(this->list_pin[i], HIGH);
        // client.publish("light1","1");
        Serial.println(String(this->list_topic[i]) + ": On");
      }
      else if(strcmp(message,"off") == 0)
      {
        digitalWrite(this->list_pin[i], LOW);
        // client.publish("light1", "0");
        Serial.println(String(this->list_topic[i]) + ": Off");
      }
    }

  }
 
}
void ESPMqtt::callback(char* topic, byte* payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    String message;
    char buff[10];
     
    for (int i = 0; i < length; i++) {
      message = message + (char)payload[i];
    }
    Serial.println(message);
    message.toCharArray(buff,10);

    SetOutPut(topic,buff);
    // memset(buff, 0, sizeof buff);
    // message = "";


}


