const uint8_t LED_PIN = 2;
const uint8_t THRESHOLD = 40;
const uint16_t SAMPLES = 1000;

int16_t cleanHallRead() {
  int32_t value = 0;
  for (uint16_t i = 0; i < SAMPLES; i++) {
    value += hallRead();
    delayMicroseconds(100);
  }
  return value / SAMPLES;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (abs(cleanHallRead()) > THRESHOLD)
    digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW);
}
