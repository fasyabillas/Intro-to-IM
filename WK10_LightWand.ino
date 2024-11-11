//Defining  variable and the GPIO pin on Arduino
int redPin= 9;
int greenPin = 10;
int  bluePin = 11;
int potPin = A2;
int sensorVal = 0;
double brightness = 0;

void setup() {
  Serial.begin(9600);
  //Defining the pins as OUTPUT
  pinMode(redPin,  OUTPUT);              
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
void  loop() {
  sensorVal = analogRead(potPin);
  brightness = (double)sensorVal / 1023;
  Serial.println(brightness);
  
  setColor(170, 0, 255, brightness); // Purple Color
  // delay(1000);
}
void setColor(int redValue, int greenValue,  int blueValue, double brightValue) {
  analogWrite(redPin, (double) redValue * brightValue);
  analogWrite(greenPin,  (double) greenValue  * brightValue);
  analogWrite(bluePin, (double) blueValue  * brightValue);
}
