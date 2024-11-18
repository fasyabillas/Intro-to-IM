int photoResistorPin = A5; // Photoresistor connected to pin A5
int ledPin = 2;           // LED connected to pin 2
int minSensor = 300;      // Minimum sensor value
int maxSensor = 800;      // Maximum sensor value

void setup() {
  Serial.begin(9600); // Start serial communication
  pinMode(ledPin, OUTPUT);

  // Blink LED to confirm setup
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Map sensor value to wind range
  int sensorValue = analogRead(photoResistorPin);
  int windValue = map(sensorValue, minSensor, maxSensor, 0, 5);

  // Send wind value to p5.js
  Serial.println(windValue);

  // Check for p5.js LED signal
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    if (data == "1,0") {
      digitalWrite(ledPin, HIGH);
      delay(100); // LED on for a short time
      digitalWrite(ledPin, LOW);
    }
  }
  delay(50); // Stabilize loop
}
