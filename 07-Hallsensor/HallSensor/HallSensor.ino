void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(hallRead());
  delay(100);
}
