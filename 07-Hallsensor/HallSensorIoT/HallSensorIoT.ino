#include <WiFi.h>
#include "ThingSpeak.h"

const uint8_t LED_PIN = 2;
const uint8_t THRESHOLD = 40;
const uint16_t SAMPLES = 1000;

const char* SSID = "SSID eintragen";
const char* PASSWORD = "Passwort eintragen";
const uint32_t CHANNEL_ID = 0; // Channel-ID eintragen
const char* API_KEY = "API-Key eintragen";

WiFiClient client;
bool isClosed = false;

int16_t cleanHallRead() {
  int32_t value = 0;
  for (uint16_t i = 0; i < SAMPLES; i++) {
    value += hallRead();
    delayMicroseconds(100);
  }
  return value / SAMPLES;
}

void updateChannel(const uint8_t value) {
  Serial.println("Neuer Wert für den Kanal: " + String(value));
  int16_t result = ThingSpeak.writeField(CHANNEL_ID, 1, value, API_KEY);
  if (result == 200) {
    Serial.println("Kanal wurde aktualisiert.");
  } else {
    Serial.println("Kanal konnte nicht aktualisiert werden: " + String(result));
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.printf("Verbunden mit %s.\n", SSID);
  Serial.printf("IP-Adresse: %s.\n", WiFi.localIP().toString().c_str());
}

void loop() {
  bool switchActivated = abs(cleanHallRead()) > THRESHOLD;
  if (switchActivated && !isClosed) {
    digitalWrite(LED_PIN, HIGH);
    isClosed = true;
    updateChannel(1);
  } else if (!switchActivated && isClosed) {
    digitalWrite(LED_PIN, LOW);
    isClosed = false;
    updateChannel(0);
  }
}
