#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_BME680.h>

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

  if (!sensor.begin(0x77)) {
    Serial.println("Konnte keinen BME680-Sensor finden.");
    return;
  }
  init_sensor(sensor);

  WiFi.softAP(SSID, PASSWORD);
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (!sensor.performReading()) {
      String message = "Konnte keine Sensor-Daten lesen.";
      Serial.println(message);
      request->send(500, "text/plain", message);
    } else {
      String message = "<!doctype html>\n";
      message += "<html>\n";
      message += "  <head>\n";
      message += "    <title>ESP32 Thermometer / Hygrometer</title>\n";
      message += "  </head>\n";
      message += "  <body>\n";
      message += "    <h1>Temperatur: ";
      message += String(sensor.temperature, 2);
      message += " &#8451;</h1>\n";
      message += "    <h1>Luftfeuchtigkeit: ";
      message += String(sensor.humidity, 0);
      message += " %</h1>\n";
      message += "  </body>\n";
      message += "</html>\n";
      request->send(200, "text/html", message);
    }
  });
 
  server.begin();
}

void loop() {}
