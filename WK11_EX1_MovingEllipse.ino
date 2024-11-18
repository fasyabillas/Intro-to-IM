int sensor = A2;

void setup() {
  Serial.begin(9600);

  // start the handshake
  while (Serial.available() <= 0) {
    digitalWrite(LED_BUILTIN, HIGH); // on/blink while waiting for serial data
    // Serial.println("0"); // send a starting message
    delay(300);            // wait 1/3 second
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }

}

void loop() {
  
  while (Serial.available()) {
    digitalWrite(LED_BUILTIN, HIGH); // led on while receiving data

    int sensorVal = analogRead(A2);
    Serial.println(sensorVal); 
    delay(5);
  }

}
