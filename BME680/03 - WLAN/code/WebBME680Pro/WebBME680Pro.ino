#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_BME680.h>
#include <SPIFFS.h>

const char* SSID = "MeinESP32";
const char* PASSWORD = "testpasswort";

AsyncWebServer server(80);
Adafruit_BME680 sensor;

void init_sensor(Adafruit_BME680& sensor) {
  sensor.setTemperatureOversampling(BME680_OS_8X);
  sensor.setHumidityOversampling(BME680_OS_2X);
  sensor.setPressureOversampling(BME680_OS_4X);
  sensor.setIIRFilterSize(BME680_FILTER_SIZE_3);
  sensor.setGasHeater(320, 150); // 320*C für 150 Millisekunden
}
 
void setup(){
  Serial.begin(115200);

  if(!SPIFFS.begin(true)){
    Serial.println("Dateisystem konnte nicht initialisiert werden.");
    return;
  }

  if (!sensor.begin(0x77)) {
    Serial.println("Konnte keinen BME680-Sensor finden.");
    return;
  }
  init_sensor(sensor);

  WiFi.softAP(SSID, PASSWORD);
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.softAPIP());

  server.on("/gauge.min.js", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/gauge.min.js");
  });
 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/index.html", String(), false, replaceVariable);
  });
 
  server.begin();
}

void loop() {}

String replaceVariable(const String& var) {
  if (var == "HUMIDITY")
    return String(sensor.readHumidity(), 0);
  if (var == "TEMPERATURE")
    return String(sensor.readTemperature(), 2);
  return String();
}
