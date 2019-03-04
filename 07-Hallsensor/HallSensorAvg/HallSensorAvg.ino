const uint16_t SAMPLES = 1000;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int32_t value = 0;
  for (uint16_t i = 0; i < SAMPLES; i++) {
    value += hallRead();
    delayMicroseconds(100);
  }
  Serial.println(value / SAMPLES);
}
