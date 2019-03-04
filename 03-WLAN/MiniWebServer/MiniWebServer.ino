#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* SSID = "SSID eintragen";
const char* PASSWORD = "Passwort eintragen";

WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.printf("Verbunden mit %s.\n", SSID);
  Serial.printf("IP-Adresse: %s.\n", WiFi.localIP().toString().c_str());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS-Responder gestartet.");
  }

  server.on("/", handleRoot);

  server.on("/make", []() {
    server.send(200, "text/plain", "Was soll ich machen?");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP-Server gestartet.");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/plain", "Hier ist der ESP32!");
}

void handleNotFound() {
  String message = "Pfad ";
  message += server.uri();
  message += " wurde nicht gefunden.\n";
  server.send(404, "text/plain", message);
}
