
#include "esp32-mqtt.h"
#include <CloudIoTCore.h>
#include <ArduinoJson.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupCloudIoT(); // Creates globals for MQTT

}

static unsigned long lastMillis = 0;
void loop()
{
  if (!mqtt->loop())
  {
    mqtt->mqttConnect();
  }

  delay(10); // <- fixes some issues with WiFi stability

  // TODO: Replace with your code here
  if (millis() - lastMillis > 60000)
  {
      StaticJsonDocument<300> doc;   
      JsonObject data = doc.to<JsonObject>();
      
      data["temp"]=String(random(40));
      data["humidity"]=String(random(40));
      
      char data_buffer[300];
      serializeJson(doc,data_buffer);
      serializeJson(doc,Serial);
    lastMillis = millis();
    publishTelemetry(data_buffer);
    Serial.println("data posted");
  }
}
