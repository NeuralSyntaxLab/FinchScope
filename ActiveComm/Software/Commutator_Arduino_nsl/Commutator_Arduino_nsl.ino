
//  Active Commutator
// 01.13.15
// WALIII

// Hall sensor controlled active commutator, driven by a servo motor
// Inspired by :
//
// Rules:
// pos > 90 : counter-clockwise movement
// pos < 90 : clockwise movement
// pos = 90 : stand still
//
// Average Sampling Rate: 8600-9000 samples per second.

#include <Servo.h>

Servo myservo;

int pos = 90;
const int analogInPin = A0;
int sensorValue = 0;        // value read from the pot
//int initialSetpoint = 510;
int setpoint = 513;
int sensitivity= 15;
int pos_change = 5;
long temp = 0;
int cnt = 0;
int setpointChangeCount = 20;
int newAvgValue = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  // setpoint setup
  Serial.println("Initial setpoint determined...");
  for (int i = 0; i < 100; ++i) {
    sensorValue = analogRead(analogInPin);
    temp = temp + sensorValue;
  }
  delay(500);
  setpoint = temp/100;
  temp = 0;
  Serial.print("Initial setpoint: ");
  Serial.println(setpoint);
  delay(1000);
  // end setpoint setup code
  
}
void loop() {


  sensorValue = analogRead(analogInPin);

  Serial.print("sensor = " );
  Serial.print(sensorValue);
  Serial.print(" ,pos = " );
  Serial.print(pos);

  if(sensorValue> setpoint+sensitivity){
      pos = pos+pos_change;
  myservo.write(pos);
  delay(15);
}

  if(sensorValue < setpoint-sensitivity){
    pos = pos-pos_change;
    myservo.write(pos);
    delay(15);
}

if(sensorValue > setpoint-sensitivity && sensorValue < setpoint+sensitivity){
pos = 90;
   myservo.write(pos);
}

if(sensorValue < setpoint-sensitivity || sensorValue > setpoint+sensitivity){
    temp = temp + sensorValue;
    cnt = cnt + 1;
    if(cnt > setpointChangeCount){
      newAvgValue = temp / cnt;
      setpoint = newAvgValue;
      temp = 0;
      cnt = 0;
    }
 } 
 else{
    temp = 0;
    cnt = 0;
    //setpoint = initialSetpoint;
  }
  Serial.print(", setpoint = ");
  Serial.println(setpoint);

if(pos > 120){
  pos = pos - 5;
  delay(50);
  myservo.write(pos);
}
if(pos < 60){
  pos = pos + 5;
  delay(50);
  myservo.write(pos);
}

  delay(100);
}
