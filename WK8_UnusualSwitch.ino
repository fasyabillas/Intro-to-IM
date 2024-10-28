void setup() {
  
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A2, INPUT);
}

void loop() {
  int greenLED = 12;
  int redLED = 10;
  int buttonState = digitalRead(A2);

  if (buttonState == HIGH){
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
  }
  else {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
  }
  
}
