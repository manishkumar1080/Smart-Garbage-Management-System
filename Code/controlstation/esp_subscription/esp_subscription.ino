#include <ESP8266WiFi.h>
#include <PubSubClient.h>   // Read the rest of the article
#include <stdlib.h>
 
String ssid="Falcon"; 
String password="marvel10";
static String temp;
static String topi;
static String batmac;


const char *mqtt_server = "m20.cloudmqtt.com";
const int mqtt_port = 17482;
const char *mqtt_user = "fkoxtvvc";
const char *mqtt_pass = "K4oJULvZgCOG";
const char *mqtt_client_name = "arduinoClient1"; // Client connections cant have the same connection name
 
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
  // Setup console
  Serial.begin(115200);  //set the baud rate
   if(Serial.available())
    {
      while(Serial.read()!='u');
      ssid=Serial.readStringUntil('\n');
      goto here;
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
    if (WiFi.status() != WL_CONNECTED) 
  {  //wifi not connected?
    WiFi.begin(ssid.c_str(), password.c_str());
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    return;
  }
  
}
 
void loop() {
  if (WiFi.status() == WL_CONNECTED) 
      {
        //client object makes connection to server
        if (!client.connected()) {
        //Authenticating the client object
        if (client.connect(MQTT::Connect("mqtt_client_name1").set_auth(mqtt_user, mqtt_pass))) {
       //Subscribe code
        client.subscribe("garbage/dusbins");
      } else {
      }
    }
    if (client.connected())
      client.loop();
  }
 client.subscribe("garbage/dusbins");
 client.set_callback(callback);
 
 while(Serial.read()!='*');
 if(temp=="B1 50%")
 {
  Serial.print("#11");
  Serial.print("\n");
 }
 else if (temp=="A1 50%")
 {
  Serial.print("#12");
  Serial.print("\n");
 }
 else if (temp=="F1 100%")
 {
  Serial.print("#13");
  Serial.print("\n");
 }
  if(temp=="B2 50%")
 {
  Serial.print("#21");
  Serial.print("\n");
 }
 else if (temp=="A2 50%")
 {
  Serial.print("#22");
  Serial.print("\n");
 }
 else if (temp=="F2 100%")
 {
  Serial.print("#23");
  Serial.print("\n");
 }
 temp=" ";  
  client.set_callback(callback);
}


 
 


