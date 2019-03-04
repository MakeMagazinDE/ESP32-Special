const uint8_t MAX_WAVE_TYPES = 4;
const uint16_t SAMPLES = 256;
const uint16_t MICROS_PER_SAMPLE = 1000000 / SAMPLES;

enum WaveTypes {
  SINE,
  TRIANGLE,
  SAWTOOTH,
  SQUARE
};

uint8_t WaveForms[MAX_WAVE_TYPES][SAMPLES] = {
   { 0 }, // Sine
   { 0 }, // Triangle
   { 0 }, // Sawtooth
   { 0 }, // Square
};

uint16_t position = 0;

void calculate_square() {
  for (uint16_t i = 0; i < SAMPLES / 2; i++) {
    WaveForms[SQUARE][i] = 255;
    WaveForms[SQUARE][SAMPLES - i - 1] = 0;
  }
}

void calculate_triangle() {
  uint8_t value = 0;
  for (uint16_t i = 0; i < SAMPLES / 2; i++) {
    WaveForms[TRIANGLE][i] = value;
    WaveForms[TRIANGLE][SAMPLES - i - 1] = value;
    value += 2;
  }
}

void calculate_sawtooth() {
  for (uint16_t i = 0; i < SAMPLES; i++) {
    WaveForms[SAWTOOTH][i] = i;
  }
}

void calculate_sine() {
  for (uint16_t i = 0; i < SAMPLES; i++) {
    uint16_t degree = map(i, 0, 255, 0, 359);
    WaveForms[SINE][i] = int(128 + 127 * sin(degree * PI / 180));
  }
}

void setup() {
  calculate_square();
  calculate_triangle();
  calculate_sawtooth();
  calculate_sine();
}
 
const WaveTypes wave_type = SAWTOOTH;
const uint16_t frequency = 10;

void loop() {
  dacWrite(DAC1, WaveForms[wave_type][position]); 
  position++;
  position %= SAMPLES;
  delayMicroseconds(MICROS_PER_SAMPLE / frequency);
}
