void setup() {
  Serial.begin(9600);
}

void loop() {
  int wert = hallRead();
  Serial.println(wert);
  delay(500);
}
