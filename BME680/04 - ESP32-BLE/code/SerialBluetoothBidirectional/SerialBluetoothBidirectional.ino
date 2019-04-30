#include "BluetoothSerial.h"

BluetoothSerial bluetooth;

void setup() {
  Serial.begin(115200);
  if (!bluetooth.begin("ESP32")) {
    Serial.println("Bluetooth konnte nicht aktiviert werden.");   
  } else {
    Serial.println("Der ESP32 kann gekoppelt werden.");
  }
}

void loop() {
  while (bluetooth.available()) {
    Serial.write(bluetooth.read());
  }
  delay(20);
}
