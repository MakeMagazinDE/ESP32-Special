void setup() {}

void loop() {
  for (uint16_t i = 0; i < 360; i++) {
    dacWrite(DAC1, int(128 + 127 * sin(i * PI / 180)));
  }
}
