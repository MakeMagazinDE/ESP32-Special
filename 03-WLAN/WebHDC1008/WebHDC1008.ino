#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_HDC1000.h>

const char* SSID = "MeinESP32";
const char* PASSWORD = "testpasswort";

AsyncWebServer server(80);
Adafruit_HDC1000 sensor = Adafruit_HDC1000();
 
void setup(){
  Serial.begin(115200);

  if (!sensor.begin(0x43)) {
    Serial.println("Konnte Temperatursensor nicht finden.");
    return;
  }
  Serial.println("Sensor wird initialisiert.");
  sensor.drySensor(); // Braucht 15 Sekunden!

  WiFi.softAP(SSID, PASSWORD);
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    String message = "<!doctype html>\n";
    message += "<html>\n";
    message += "  <head>\n";
    message += "    <title>ESP32 Thermometer / Hygrometer</title>\n";
    message += "  </head>\n";
    message += "  <body>\n";
    message += "    <h1>Temperatur: ";
    message += String(sensor.readTemperature(), 2);
    message += " &#8451;</h1>\n";
    message += "    <h1>Luftfeuchtigkeit: ";
    message += String(sensor.readHumidity(), 0);
    message += " %</h1>\n";
    message += "  </body>\n";
    message += "</html>\n";
    request->send(200, "text/html", message);
  });
 
  server.begin();
}

void loop() {}
