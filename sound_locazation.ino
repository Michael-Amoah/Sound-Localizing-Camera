#include <Servo.h>

Servo servo;
const int rightSensor = A0;
const int leftSensor = A5;
int servoPin = 13;
int rightValue;
int leftValue;
int angle;
int calibratedRight = 330;
int calibratedLeft = 312;
void setup() {
servo.attach(servoPin);
Serial.begin(9600);
}

void loop() {
  rightValue = analogRead(rightSensor);
  leftValue = analogRead(leftSensor);
  Serial.print("Right:");
  Serial.print(rightValue);
  Serial.print(",");
  Serial.print("Left:");
  Serial.println(leftValue);
  int rightDev = abs(rightValue - calibratedRight);
  int leftDev = abs(leftValue - calibratedLeft);
  if (  rightDev > 50 || leftDev > 60 ) {
      (rightDev > leftDev) ? servo.write(0) : servo.write(180);
      delay(50);
    }
  //angle = map(soundValue, 0, 1023, 0, 180);

  //servo_test.write(angle);

  //delay(50);
}