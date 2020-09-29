#include <Arduino.h>
#include <WiFi.h>

#include <ESPStringUtils.h>

WiFiClient wifi;//needed to stay on global scope


void setup() {
  
  Serial.begin(115200);
  WiFi.begin("ssid","pass");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  byte mac[6];
  WiFi.macAddress(mac);
  String topic = "espnow/"+hextab_to_string(mac);

  Serial.print(topic);
}

void loop() {
}
