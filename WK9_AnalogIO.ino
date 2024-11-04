int sensor = A2;
int yellowLED = 6;
int redLED = 10;
int brightness= 0;
int button = A5;
bool buttonState;

void setup() {
  Serial.begin(9600);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  int sensorVal = analogRead(sensor);
  Serial.println(sensorVal);

  // constraining and mapping sensor reading to range 0 - 255
  sensorVal = constrain(sensorVal, 700, 725);
  brightness = map(sensorVal, 725, 700, 0, 255);

  // set brightness of led
  analogWrite(yellowLED, brightness);

  // switch logic
  buttonState = digitalRead(button);
  if (buttonState){
    digitalWrite(redLED, HIGH);
  } else {
    digitalWrite(redLED, LOW);
  }

  
  // wait for 30 msecs to see dimming effect
  delay(30); 
}