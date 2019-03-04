const uint16_t SAMPLES = 256;
uint8_t WaveForm[SAMPLES] = { 0 };
uint16_t position = 0;

void setup() {
  for (uint16_t i = 0; i < SAMPLES; i++) {
    uint16_t degree = map(i, 0, 255, 0, 359);
    WaveForm[i] = int(128 + 127 * sin(degree * PI / 180));
  }
}
 
void loop() {
  dacWrite(DAC1, WaveForm[position++]); 
  position %= SAMPLES;
}
