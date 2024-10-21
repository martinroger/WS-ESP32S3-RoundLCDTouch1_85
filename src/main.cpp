#include <Arduino.h>
#include <ESP_Panel_Library.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(millis());
  delay(1000);
}
