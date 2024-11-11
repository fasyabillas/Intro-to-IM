// declaring variables
int redPin= 9;
int greenPin = 10;
int  bluePin = 11;
int potPin = A2;
int sensorVal = 0;
double brightness = 0;

void setup() {
  Serial.begin(9600);
  // defining the pins as output
  pinMode(redPin,  OUTPUT);              
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void  loop() {
  // reading sensor value from potentiometer
  sensorVal = analogRead(potPin);
  brightness = (double)sensorVal / 1023;
  Serial.println(brightness);
  
  setColor(170, 0, 255, brightness); // purple Color
}

// function from (https://projecthub.arduino.cc/semsemharaz/interfacing-rgb-led-with-arduino-b59902)
void setColor(int redValue, int greenValue,  int blueValue, double brightValue) {
  analogWrite(redPin, (double) redValue * brightValue);
  analogWrite(greenPin,  (double) greenValue  * brightValue);
  analogWrite(bluePin, (double) blueValue  * brightValue);
}
