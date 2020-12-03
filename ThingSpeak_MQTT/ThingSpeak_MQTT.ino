#include "PubSubClient.h" 
#include  <ESP8266WiFi.h> 

const char* ssid = "realme 3 Pro";
const char* password = "khusi123";
//char* topic="channels/<channelID>/publish/<channelAPI>
const char* channel_ID = "1205518";
const char* api_key= "T7PWE2BC8XAUA7M0";
char* topic = "channels/1205518/publish/T7PWE2BC8XAUA7M0"; 
char* server = "mqtt.thingspeak.com";
String clientName="ESP-Thingspeak";

WiFiClient wifiClient;
PubSubClient client(server, 1883, wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

void setup() {
  Serial.begin(115200);
  //Wifi details
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");



  Serial.print("Connecting to ");
  Serial.print(server);
  Serial.print(" as ");
  Serial.println(clientName);
  //connect to server using a unique client name
  if (client.connect((char*) clientName.c_str())) {
    Serial.println("Connected to MQTT broker");
    Serial.print("Topic is: ");
    Serial.println(topic);
  }
  else {
    Serial.println("MQTT connect failed");
    Serial.println("Will reset and try again...");
    abort();
  }
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){
    String payload="field3="+ String(random(50)) ;
    client.loop();//to keep connection alive but it does not work
    //If connection is active posts data
    if (client.connected()){
      Serial.print("Sending payload: ");
      Serial.println(payload);
    
      if (client.publish(topic, (char*) payload.c_str())) {
        Serial.println("Publish ok");
      }
      else {
        Serial.println("Publish failed");
      }
    }
    else{
      //if disconnected then reconnects
      Serial.println("mqtt disconnected");
      if (client.connect((char*) clientName.c_str())) {
        Serial.println("Connected to MQTT broker");
        Serial.print("Topic is: ");
        Serial.println(topic);
       }
      else {
        Serial.println("MQTT connect failed");
        Serial.println("Will reset and try again...");
        abort();
      }
    
    }
  }
  else{
    Serial.println("No wifi");
  }
  delay(10000);
}
