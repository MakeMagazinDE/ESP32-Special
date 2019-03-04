#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_HDC1000.h>
#include <SPIFFS.h>

const char* SSID = "MeinESP32";
const char* PASSWORD = "testpasswort";

AsyncWebServer server(80);
Adafruit_HDC1000 sensor = Adafruit_HDC1000();
 
void setup(){
  Serial.begin(115200);

  if(!SPIFFS.begin(true)){
    Serial.println("Dateisystem konnte nicht initialisiert werden.");
    return;
  }

  if (!sensor.begin(0x43)) {
    Serial.println("Konnte Temperatursensor nicht finden.");
    return;
  }
  Serial.println("Sensor wird initialisiert.");
  sensor.drySensor(); // Braucht 15 Sekunden!

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
