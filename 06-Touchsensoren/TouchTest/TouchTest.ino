void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(touchRead(T0));
  delay(100);
}
