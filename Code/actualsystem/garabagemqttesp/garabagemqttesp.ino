#include <ESP8266WiFi.h>
#include <PubSubClient.h> 
#include <stdlib.h>
 
String ssid; 
String password ;
static String temp;
static String topi;
static String st,st1;
static String top;

 
const char *mqtt_server = "m20.cloudmqtt.com";
const int mqtt_port = 17482;
const char *mqtt_user = "fkoxtvvc";
const char *mqtt_pass = "K4oJULvZgCOG";
const char *mqtt_client_name = "arduinoClient";
 
#define BUFFER_SIZE 100
 

WiFiClient wclient;  //Declares a WifiClient Object using ESP8266WiFi
PubSubClient client(wclient, mqtt_server,mqtt_port);  //instanciates client object
 
//Function is called when, a message is recieved in the MQTT server.
void callback(const MQTT::Publish& pub) {
  topi=pub.topic();
  if (pub.has_stream()) {
    uint8_t buf[BUFFER_SIZE];
    int read;
    while (read = pub.payload_stream()->read(buf, BUFFER_SIZE)) {
    }
    pub.payload_stream()->stop();    
  } else
    temp=pub.payload_string();
      
}
 
void setup()  {
  Serial.begin(115200);
   while(1)
  {
    if(Serial.available())
    {
      while(Serial.read()!='u');
      ssid=Serial.readStringUntil('\n');
      goto here;
    }
  } 
  here:
    while(1)
  {
    if(Serial.available())
    {
      while(Serial.read()!='p');
      password=Serial.readStringUntil('\n');
      goto there;
    }
  }
  there:
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid.c_str(), password.c_str());
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
      return;
  }
  
}
 
void loop()
{
   if (WiFi.status() == WL_CONNECTED) 
      {
        //client object makes connection to server
        if (!client.connected()) {
        //Authenticating the client object
        if (client.connect(MQTT::Connect("mqtt_client_name").set_auth(mqtt_user, mqtt_pass))) {
       //Subscribe code
       // client.subscribe("garbage");
      } else {
      }
    }
    if (client.connected())
      client.loop();
 
  }
     client.set_callback(callback);
     Serial.print("*");
     if(Serial.available())    
      {
        top=Serial.readStringUntil('!');
        st=Serial.readStringUntil('\a');
        top=Serial.readStringUntil('#');
        st1=Serial.readStringUntil('\a');
        client.publish("garbage/dusbins", st);
        delay(100);
        client.publish("garbage/dusbins", st1);
        delay(100);
        client.set_callback(callback);
      }
}
