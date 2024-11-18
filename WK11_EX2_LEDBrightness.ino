int LED = 6;
int brightness;

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

  pinMode(LED, OUTPUT);

}

void loop() {
  
  while (Serial.available()) {
    
    brightness = Serial.parseInt();
    if (Serial.read() == '\n'){
      analogWrite(LED, brightness);
    }
  }

}
