#define LED 5

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  delay(1000);
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
}
