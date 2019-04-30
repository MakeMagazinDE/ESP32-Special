#include <WiFi.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Suche läuft.");
  const uint8_t n = WiFi.scanNetworks();
    
  if (n == 0) {
    Serial.println("Kein Netzwerk gefunden.");
  } else {
    Serial.print(n);
    Serial.println(" Netzwerke in Sicht.");
    Serial.println("---------------------------------+------+----------------");
    Serial.println("               SSID              | RSSI |    AUTH MODE   ");
    Serial.println("---------------------------------+------+----------------");
    for (uint8_t i = 0; i < n; i++) {
      Serial.printf("%32.32s | ", WiFi.SSID(i).c_str());
      Serial.printf("%4d | ", WiFi.RSSI(i));
      Serial.printf("%15s\n", authModeToText(WiFi.encryptionType(i)).c_str());
    }
  }
  Serial.println("");
  delay(5000);
}

String authModeToText(wifi_auth_mode_t authMode) { 
  switch (authMode) {
    case WIFI_AUTH_OPEN:
      return "Offen";
    case WIFI_AUTH_WEP:
      return "WEP";
    case WIFI_AUTH_WPA_PSK:
      return "WPA PSK";
    case WIFI_AUTH_WPA2_PSK:
      return "WPA2 PSK";
    case WIFI_AUTH_WPA_WPA2_PSK:
      return "WPA/WPA2 PSK";
    case WIFI_AUTH_WPA2_ENTERPRISE:
      return "WPA2 ENTERPRISE";
    case WIFI_AUTH_MAX:
      return "MAX";
    default:
      return "Unbekannt";  
  }
}
