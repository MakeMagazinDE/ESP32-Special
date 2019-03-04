]#include "Adafruit_HDC1000.h"
 
Adafruit_HDC1000 sensor = Adafruit_HDC1000();

void setup() {
  Serial.begin(115200);
 
  if (!sensor.begin(0x43)) {
    Serial.println("Konnte Temperatursensor nicht finden.");
    return;
  }
  Serial.println("Sensor wird initialisiert.");
  sensor.drySensor(); // Braucht 15 Sekunden!
}
 
void loop() {
  Serial.printf("Temperatur: %.2f C\t", sensor.readTemperature());
  Serial.printf("Luftfeuchtigkeit: %.2f %%\n", sensor.readHumidity());
  delay(1000);
}
