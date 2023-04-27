#include <Servo.h>
Servo servo;
const int rightSensor = A5;
const int leftSensor = A0;
int servoPin = 13;
int rightValue;
int leftValue;
int angle;

int sampleLeft[] = {0,0,0,0,0,0,0,0,0,0};
int sampleRight[] = {0,0,0,0,0,0,0,0,0,0};
int maxSample[] = {0,0};
int t =0;
int averageLeft = 0;
int averageRight = 0;
int samplingTime;
int leftDeltaMax;
int rightDeltaMax;


void setup() {
  pinMode(rightSensor, INPUT);
  pinMode(leftSensor, INPUT);
  servo.attach(servoPin);

  Serial.begin(9600);
}

int getMaximum(int arr[], int length) {
  int max = 0;
  for (int i = 0; i < length; ++i) {
    if (arr[i] > max ) {
      max = arr[i];
    }
  }
  return max;
}

int getMin(int arr[], int length) {
  int min = 10000;
  for (int i = 0; i < length; ++i) {
    if (arr[i] < min ) {
      min = arr[i];
    }
  }
  return min;
}

// void getSample() {
//   for (int i = 0; i < 10; ++i) {
//     sampleRight[i] = analogRead(rightSensor);

//   }
//   for (int i = 0; i < 10; ++i) {
//     sampleLeft[i] = analogRead(leftSensor);
//   }
// }

int getAverage(int arr[], int length) {
  int sum = 0;
  for (int i = 0; i < length; ++i) {
    sum += arr[i];
  }
  return sum/length;
}
void calibration() {
  int calibrationArr[100];
  for (int i = 0; i < 100; ++i) {
    calibrationArr[i] = analogRead(rightSensor);
  }
  averageRight = getAverage(calibrationArr, 50);
  int rightMax = getMaximum(calibrationArr, 50);
  int rightMin = getMin(calibrationArr,50);

  rightDeltaMax = max(abs(averageRight - rightMax), abs(averageRight - rightMin));
   for (int i = 0; i < 100; ++i) {
    calibrationArr[i] = analogRead(leftSensor);
  }
  int leftMax = getMaximum(calibrationArr, 50);
  int leftMin = getMin(calibrationArr, 50);
  averageLeft = getAverage(calibrationArr, 50);

  leftDeltaMax = max(abs(averageLeft - leftMax), abs(averageLeft - leftMin));

}

void loop() {

  // if (t  == 100) {
  //   calibration();
  //   t = 0;
  // }
  calibration();
  rightValue = analogRead(rightSensor);
  leftValue = analogRead(leftSensor);
  Serial.print("Right:");
  Serial.print(rightValue);
  Serial.print(",");
  Serial.print("Left:");
  Serial.println(leftValue);
  Serial.print(",");
  Serial.print("LeftAverage:");
  Serial.println(averageLeft);
  Serial.print(",");
  Serial.print("RightAverage:");
  Serial.println(averageRight);

  // getSample();


  if (leftDeltaMax < abs(averageLeft -leftValue)) {
    leftDeltaMax = abs(leftValue - averageLeft);
  }
  if (rightDeltaMax < abs(rightValue- averageRight)) {
    rightDeltaMax = abs(rightValue- averageRight);
  }

  if ( !(averageRight == 0) && !(averageLeft && 0)) {
    if ( leftDeltaMax > 100 ) {
      if ( rightDeltaMax > leftDeltaMax) {
        servo.write(0);
        delay(1000);
      }
      else {
        servo.write(180);
        delay(1000);
      }
    }
    else if ( rightDeltaMax > 100) {
      if ( rightDeltaMax > leftDeltaMax ) {
        servo.write(0);        
        delay(1000);
      }
      else {
        servo.write(180);
        delay(1000);
      }
    }
  }
  // t++;



  // for (int i = 0; i < 5; ++i) {
  //   sample1[i] = analogRead(rightSensor);
  //   sample2[i] = analogRead(leftSensor);
  // }

//   if (leftValue == LOW && rightValue == HIGH) {
//     servo.write(180);
//     delay(1000);
//   }
//   else if ( leftValue == HIGH && rightValue == LOW) {
//     servo.write(0);
//     delay(1000);
// }
  //int rightDev = abs(rightValue - calibratedRight);
  //int leftDev = abs(leftValue - calibratedLeft);
  // if (  rightDev > 50 || leftDev > 60 ) {
  //     (rightDev > leftDev) ? servo.write(0) : servo.write(180);
  //     delay(50);
  //   }
  // if ( lefValue )
  //angle = map(soundValue, 0, 1023, 0, 180);

  //servo_test.write(angle);

}