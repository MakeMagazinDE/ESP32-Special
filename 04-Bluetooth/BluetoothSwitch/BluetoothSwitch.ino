#include "BluetoothSerial.h"

const uint8_t LED_PIN = 2;

BluetoothSerial bluetooth;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  if (!bluetooth.begin("ESP32")) {
    Serial.println("Bluetooth konnte nicht aktiviert werden.");   
  } else {
    Serial.println("Der ESP32 kann gekoppelt werden.");
  }
}

void loop() {
  while (bluetooth.available()) {
    const int c = bluetooth.read();
    Serial.write(c);
    if (c == '1') {
      digitalWrite(LED_PIN, HIGH);
    } else if (c == '0') {
      digitalWrite(LED_PIN, LOW);
    }
  }
  delay(20);
}
