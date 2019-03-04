const uint8_t THRESHOLD = 20;
const uint8_t LED_PIN = 2;

bool touchedT0 = false;
bool touchedT3 = false;

void T0wasActivated() {
  touchedT0 = true;
}

void T3wasActivated() {
  touchedT3 = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  touchAttachInterrupt(T0, T0wasActivated, THRESHOLD);
  touchAttachInterrupt(T3, T3wasActivated, THRESHOLD);
}

void loop(){
  if (touchedT0){
    touchedT0 = false;
    Serial.println("Sensor T0");
    digitalWrite(LED_PIN, HIGH);
  }
  
  if (touchedT3){
    touchedT3 = false;
    Serial.println("Sensor T3");
    digitalWrite(LED_PIN, LOW);
  }
}
