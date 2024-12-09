#include <Servo.h>
#include <LiquidCrystal.h>

Servo myservo;
const int servoPin = 6;
int pos = 0;

const int trigPin = 10;
const int echoPin = 11;

const int pressPin1 = A0;
const int pressPin2 = A1;

unsigned long sensorTime = 0;
unsigned long servoTime = 0;
bool increasing = true;

float duration, distance;
int pressure1, pressure2;

bool isDown = false;

const int rs = 9, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String name = "", previousName = "";
int offset;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pressPin1, INPUT);
  pinMode(pressPin2, INPUT);
  myservo.attach(servoPin);

  if (Serial.available() <= 0){
    // send a starting message
    Serial.println("0,0"); 
  }
  lcd.begin(16, 2);
}

void loop() {
  unsigned long time = millis();

  int interval1 = 100;
  if (time - sensorTime >= interval1) {
    
    sensorTime = time;

    // reading values from ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // calculating distance
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;

    // reading pressure values
    pressure1 = analogRead(pressPin1);
    pressure2 = analogRead(pressPin2);
    
    // Sends distance values
    Serial.print(distance);
    Serial.print(',');
    // Sends boolean value of whether paw is down or not
    Serial.print(isDown);
    // Sends pressure values
    Serial.print(',');
    Serial.print(pressure1);
    Serial.print(',');
    Serial.println(pressure2);
    
  }

  int servInt = 5;

  // check if it's time to update the servo position
  
  if (time - servoTime >= servInt) {
    // update the last move time
    servoTime = time; 

    if (distance <= 10 && increasing) {
      // increment position
      pos++; 
      if (pos >= 90) {
        // change direction
        increasing = false; 
      }
    } else if (distance > 10 && !increasing){
      // decrement position
      pos--; 
      if (pos <= 0) {
        // change direction
        increasing = true; 
      }
    } 
    // move the servo to the new position
    myservo.write(pos); 
  }

  // updating value of isDown
  if (pos == 90){
    isDown = true;
  } else{
    isDown = false;
  }

  if (Serial.available()){

    name = Serial.readStringUntil('\n');
    name.trim();
    // only update LCD if the name has changed
    if (name != previousName) {
      // update the last displayed name
      previousName = name;
      // center-align the name
      int offset = (16 - name.length()) / 2; 
      // reset to the first row
      lcd.setCursor(0, 0);
      // clear the row without lcd.clear()
      lcd.print("                "); 
      // position the cursor to the beginning
      lcd.setCursor(offset, 0);
      // display the new name
      lcd.print(name);                     
    }
    
  }

}