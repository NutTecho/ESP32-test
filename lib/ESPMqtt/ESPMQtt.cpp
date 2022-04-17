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
    // for(int i = 0; i < this->sizelist ; i++)
    // {
    //   strcpy(this->list_topic[i],topic[i]);
    // }
  
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
      // char buff[100];
      // sprintf(buff,"%d",atoi(list_topic[i]));
      // Serial.println(buff);
      // list_topic[i].toCharArray(msg,20);
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
  //  Serial.println((String)list_topic[0]);
    if(strcmp(topic,"light1") == 0) 
    {
      if(strcmp(message,"on") ==0){
        digitalWrite(2, HIGH);
        // client.publish("light1","1");
        Serial.println("light1 : On");
      }
      else if(strcmp(message,"off") == 0){
        digitalWrite(2, LOW);
        // client.publish("light1", "0");
        Serial.println("light1 : Off");
      }
    }

     if(strcmp(topic,"motor1") == 0) 
    {
      if(strcmp(message,"on") ==0){
        digitalWrite(19, LOW);
        // client.publish("light1","1");
        Serial.println("motor1 : On");
      }
      else if(strcmp(message,"off") == 0){
        digitalWrite(19, HIGH);
        // client.publish("light1", "0");
        Serial.println("motor1 : Off");
      }
    }

     if(strcmp(topic,"motor2") == 0) 
    {
      if(strcmp(message,"on") ==0){
        digitalWrite(21, LOW);
        // client.publish("light1","1");
        Serial.println("motor2 : On");
      }
      else if(strcmp(message,"off") == 0){
        digitalWrite(21, HIGH);
        // client.publish("light1", "0");
        Serial.println("motor2 : Off");
      }
    }

    if(strcmp(topic,"fog1") == 0) 
    {
      if(strcmp(message,"on") ==0){
        digitalWrite(4, HIGH);
        // client.publish("light1","1");
        Serial.println("fog1 : On");
      }
      else if(strcmp(message,"off") == 0){
        digitalWrite(4, LOW);
        // client.publish("light1", "0");
        Serial.println("fog1 : Off");
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

    Serial.println(list_topic[3]);

    
    SetOutPut(topic,buff);

    // char buff[100];
    // sprintf(buff,"address : %d",atoi(list_topic[0]));
    // Serial.println(buff);

    // Serial.println(this->list_topic[0][0]);
    // Serial.println(this->list_topic[0][1]);
    // Serial.println(this->list_topic[0][2]);
    // Serial.println(this->list_topic[0][3]);
    // Serial.println(this->list_pin[0]);
    // Serial.println(strlen(topic));
    // Serial.println(sizeof(topic));

    // for (int j=0; j < this->sizelist ; j++)
    // {
    //   Serial.println(this->list_topic[j]);
    //   if (strcmp(topic,this->list_topic[j]) == 0)
    //   {
    //       Serial.println(topic);
    //       Serial.print(list_topic[j]);
          // char msg[100];
          // list_topic[i].toCharArray(msg,100);
         
    //   }
    // }

}


