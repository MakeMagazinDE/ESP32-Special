void setup() {
  Serial.begin(115200L);
}

void loop() {
  log_e("Error");
  log_w("Warning");
  log_i("Info");
  log_d("Debug");
  log_v("Verbose");
  delay(1000);
}
