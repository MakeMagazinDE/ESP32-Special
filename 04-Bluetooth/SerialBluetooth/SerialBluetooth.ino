#include "BluetoothSerial.h"
 
BluetoothSerial bluetooth;
 
void setup() {
  bluetooth.begin("ESP32");
}
 
void loop() { 
  bluetooth.println("Hier bin ich!");
  delay(1000);
}
