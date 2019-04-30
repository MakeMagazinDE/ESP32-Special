#include <Adafruit_BME680.h>

const float SEALEVEL_PRESSURE = 1013.25; // hPa

Adafruit_BME680 sensor;

void init_sensor(Adafruit_BME680& sensor) {
  sensor.setTemperatureOversampling(BME680_OS_8X);
  sensor.setHumidityOversampling(BME680_OS_2X);
  sensor.setPressureOversampling(BME680_OS_4X);
  sensor.setIIRFilterSize(BME680_FILTER_SIZE_3);
  sensor.setGasHeater(320, 150); // 320*C für 150 Millisekunden
}

void setup() {
  Serial.begin(115200); 
  if (!sensor.begin(0x77)) {
    Serial.println("Konnte keinen BME680-Sensor finden.");
    return;
  }
  init_sensor(sensor);
}
 
void loop() {
  if (!sensor.performReading()) {
    Serial.println("Konnte keine Sensor-Daten lesen.");
  } else {
    Serial.printf("Temperatur = %.2f *C\n", sensor.temperature);
    Serial.printf("Luftdruck = %.2f hPa\n", sensor.pressure / 100.0);
    Serial.printf("Luftfeuchtigkeit = %.2f %%\n", sensor.humidity);
    Serial.printf("Gas-Widerstand = %.2f kOhm\n", sensor.gas_resistance / 1000.0);
    Serial.printf("Geschätzte Höhe = %.2f m\n\n", sensor.readAltitude(SEALEVEL_PRESSURE));
  }
  delay(3000);
}
