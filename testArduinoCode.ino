#include <Servo.h>
#include <LiquidCrystal.h>

Servo myservo;
const int servoPin = 6;
int pos = 0;

const int trigPin = 10;
const int echoPin = 11;

const int pressPin = A5;

unsigned long sensorTime = 0;
unsigned long servoTime = 0;
bool increasing = true;

float duration, distance;
int pressure;

const int rs = 9, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String name = "", previousName = "";
int offset;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pressPin, INPUT);
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
    // save the last time you blinked the LED
    sensorTime = time;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;
    pressure = analogRead(pressPin);
    // Serial.print("Distance: ");
    Serial.print(distance);
    // Serial.print("  Pressure: ");
    Serial.print(',');
    Serial.println(pressure);
  }

  int servInt = 5;

  // check if it's time to update the servo position
  
  if (time - servoTime >= servInt) {
    servoTime = time; // update the last move time

    if (distance <= 10 && increasing) {
      pos++; // increment position
      if (pos >= 90) {
        increasing = false; // change direction
      }
    } else if (distance > 10 && !increasing){
      pos--; // decrement position
      if (pos <= 0) {
        increasing = true; // change direction
      }
    }
    myservo.write(pos); // move the servo to the new position

  }

  if (Serial.available()){
    name = Serial.readStringUntil('\n');
    name.trim();
    // only update LCD if the name has changed
    if (name != previousName) {
      previousName = name;                // update the last displayed name
      int offset = (16 - name.length()) / 2; // center-align the name
      lcd.setCursor(0, 0);                // reset to the first row
      lcd.print("                ");      // clear the row without lcd.clear()
      lcd.setCursor(offset, 0);           // position the cursor
      lcd.print(name);                     // display the new name
    }
    
  }

  

  
}