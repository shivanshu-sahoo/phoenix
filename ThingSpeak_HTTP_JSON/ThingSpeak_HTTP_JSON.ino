#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* ssid = "realme 3 Pro";
const char* password = "khusi123";

const char* server_name = "http://api.thingspeak.com/update";
String api_key = "T7PWE2BC8XAUA7M0";

unsigned long last_time = 0;
unsigned long timer_delay = 1000;

void setup() {
  Serial.begin(9600);
  //Wifi connection
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");


}

void loop() {
  if ((millis() - last_time) > timer_delay) {
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      http.begin(server_name);//connecting to the server
      
      StaticJsonDocument<300> doc;   //creating json
      JsonObject JSON_encoder = doc.to<JsonObject>();

      JSON_encoder["api_key"]=api_key;
      JSON_encoder["field1"]=String(random(40));
      JSON_encoder["field2"]=String(random(40));
      
      char JSON_message_buffer[300];
      serializeJson(doc,JSON_message_buffer);
      serializeJsonPretty(doc, Serial);
                  
      http.addHeader("Content-Type", "application/json");//adding content type as a header
      int http_response_code = http.POST(JSON_message_buffer);//posting the data
     
      Serial.print("HTTP Response code: ");
      Serial.println(http_response_code);
        
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    last_time = millis();
  }
}
