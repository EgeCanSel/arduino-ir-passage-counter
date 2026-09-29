const byte SENSOR_PIN = 2;

int previousState;
unsigned long passageCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
  previousState = digitalRead(SENSOR_PIN);
}

void loop() {
  int currentState = digitalRead(SENSOR_PIN);

  // The sensor is active-low: count only a transition from clear to detected.
  if (previousState == HIGH && currentState == LOW) {
    passageCount++;
    unsigned long eventTimeMs = millis();

    Serial.print(eventTimeMs);
    Serial.print(',');
    Serial.println(passageCount);
  }

  previousState = currentState;
  delay(20);
}
