#include <Servo.h>
Servo servo;
const int rightSensor = A5;
const int rightMidSensor = A4;
const int leftSensor = A0;
const int middleSensor = A3;
const int leftMidSensor = A2;
int servoPin = 13;

int rightMidValue;
int rightValue;
int middleValue;
int leftMidValue;
int leftValue;
int angle;

//int sampleLeft[] = {0,0,0,0,0,0,0,0,0,0};
//int sampleRight[] = {0,0,0,0,0,0,0,0,0,0};
int maxSample[] = {0,0};
int t =0;
int averageLeft = 0;
int averageLeftMid = 0;
int averageMiddle = 0;
int averageRight = 0;
int averageRightMid = 0;
int samplingTime;
int leftDeltaMax;
int leftMidDeltaMax;
int middleDeltaMax;
int rightDeltaMax;
int rightMidDeltaMax;


void setup() {
  pinMode(rightSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightMidSensor, INPUT);
  pinMode(leftMidSensor, INPUT);
  pinMode(leftSensor, INPUT);
  servo.attach(servoPin);
  servo.write(90);
  delay(10000);
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
  int rightArr[100];
  int leftArr[100];
  int midArr[100];
  int rightMidArr[100];
  int leftMidArr[100];
  
  for (int i = 0; i < 100; ++i) {
//    calibrationArr[i] = analogRead(rightSensor);
    rightArr[i] = analogRead(rightSensor);
    leftArr[i] = analogRead(leftSensor);
    midArr[i] = analogRead(middleSensor);
    rightMidArr[i] = analogRead(rightMidSensor);
    leftMidArr[i] = analogRead(leftMidSensor);
  }
  averageRight = getAverage(rightArr, 50);
  int rightMax = getMaximum(rightArr, 50);
  int rightMin = getMin(rightArr,50);

  rightDeltaMax = max(abs(averageRight - rightMax), abs(averageRight - rightMin));
//   for (int i = 0; i < 100; ++i) {
//    calibrationArr[i] = analogRead(leftSensor);
//  }
  int leftMax = getMaximum(leftArr, 50);
  int leftMin = getMin(leftArr, 50);
  averageLeft = getAverage(leftArr, 50);

  leftDeltaMax = max(abs(averageLeft - leftMax), abs(averageLeft - leftMin));
//
//  for (int i = 0; i < 100; ++i) {
//    calibrationArr[i] = analogRead(middleSensor);
//  }
  int middleMax = getMaximum(midArr, 50);
  int middleMin = getMin(midArr, 50);
  averageMiddle = getAverage(midArr, 50);

  middleDeltaMax = max(abs(averageMiddle - middleMax), abs(averageMiddle - middleMin));

//  for (int i = 0; i < 100; ++i) {
//    calibrationArr[i] = analogRead(rightMidSensor);
//  }
  int rightMidMax = getMaximum(rightMidArr, 50);
  int rightMidMin = getMin(rightMidArr, 50);
  averageRightMid = getAverage(rightMidArr, 50);

  rightMidDeltaMax = max(abs(averageRightMid - rightMidMax), abs(averageRightMid - rightMidMin));

//  
//  for (int i = 0; i < 100; ++i) {
//    calibrationArr[i] = analogRead(leftMidSensor);
//  }
  int leftMidMax = getMaximum(leftMidArr, 50);
  int leftMidMin = getMin(leftMidArr, 50);
  averageLeftMid = getAverage(leftMidArr, 50);

  leftMidDeltaMax = max(abs(averageLeftMid - leftMidMax), abs(averageLeftMid - leftMidMin));

}

int largestDelta() {
  int deltas[] = {leftDeltaMax, middleDeltaMax, rightDeltaMax, leftMidDeltaMax, rightMidDeltaMax};
  int largestDeltaIndex = 0;
  int largestDelta = 0;
  for (int i = 0; i < 5; ++i) {
    if ( abs(deltas[i]) > largestDelta ) {
      largestDelta = abs(deltas[i]);
      largestDeltaIndex = i;
    }
  }
  return largestDeltaIndex;
  
}

void loop() {

  // if (t  == 100) {
  //   calibration();
  //   t = 0;
  // }
  calibration();
  rightValue = analogRead(rightSensor);
  leftValue = analogRead(leftSensor);
  middleValue = analogRead(middleSensor);
  rightMidValue = analogRead(rightMidSensor);
  leftMidValue = analogRead(leftMidSensor);
  // Serial.print("Right:");
  // Serial.print(rightValue);
  // Serial.print(",");
  // Serial.print("Left:");
  // Serial.println(leftValue);
  // Serial.print(",");
  // Serial.print("Middle:");
  // Serial.println(middleValue);
  // Serial.print(",");
  // Serial.print("LeftAverage:");
  // Serial.println(averageLeft);
  // Serial.print(",");
  // Serial.print("RightAverage:");
  // Serial.println(averageRight);
  // Serial.print(",");
  // Serial.print("MiddleAverage:");
  // Serial.println(averageMiddle);

  // getSample();


  if (leftDeltaMax < abs(averageLeft -leftValue)) {
    leftDeltaMax = abs(leftValue - averageLeft);
  }
  if (rightDeltaMax < abs(rightValue- averageRight)) {
    rightDeltaMax = abs(rightValue- averageRight);
  }
  if (middleDeltaMax < abs(middleValue - averageMiddle)) {
    middleDeltaMax = abs(middleValue - averageMiddle);
  }
  if (rightMidDeltaMax < abs(rightMidValue - averageRightMid)) {
    rightMidDeltaMax = abs(rightMidValue - averageRightMid);
  }
  if (leftMidDeltaMax < abs(leftMidValue - averageLeftMid)) {
    leftMidDeltaMax = abs(leftMidValue - averageLeftMid);
  }
   if ( averageRight != 0 && averageLeft != 0 && averageMiddle != 0 && averageRightMid != 0 && averageLeftMid != 0) {
  switch (largestDelta()) {
    case 0: // left
      if (abs(leftDeltaMax) > 100) {
        servo.write(0);
        delay(1000);
      }
      break;
    case 1: // middle
      if (abs(middleDeltaMax) > 100) {
        servo.write(90);
        delay(1000);
      }
      break;
    case 2: // right
      if (abs(rightDeltaMax) > 100) {
        servo.write(180);
        delay(1000);
      }
      break;
    case 3: // rightMid
      if (abs(leftMidDeltaMax) > 100) {
        servo.write(45);
        delay(1000);
      }
      break;
      case 4: // leftMid
      if (abs(rightMidDeltaMax) > 100) {
        servo.write(135);
        delay(1000);
      }
      break;
  }
   }
    Serial.print(",");
  Serial.print("MiddleDelta:");
  Serial.println(middleDeltaMax);
   Serial.print(",");
  Serial.print("RightDelta:");
  Serial.println(rightDeltaMax);
   Serial.print(",");
  Serial.print("LeftDelta:");
  Serial.println(leftDeltaMax);
  Serial.print(",");
  Serial.print("RightMidDelta:");
  Serial.println(rightDeltaMax);
  Serial.print(",");
  Serial.print("LeftMidDelta:");
  Serial.println(leftMidDeltaMax);

//  if ( !(averageRight == 0) && !(averageLeft && 0)) {
//    if ( leftDeltaMax > 100 ) {
//      if ( rightDeltaMax > leftDeltaMax) {
//        servo.write(0);
//        delay(1000);
//      }
//      else {
//        servo.write(180);
//        delay(1000);
//      }
//    }
//    else if ( rightDeltaMax > 100) {
//      if ( rightDeltaMax > leftDeltaMax ) {
//        servo.write(0);        
//        delay(1000);
//      }
//      else {
//        servo.write(180);
//        delay(1000);
//      }
//    }
//  }
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
