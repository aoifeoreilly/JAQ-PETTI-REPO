/*
  WallDetection.h - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
*/
#include "Arduino.h"
#include "LightSensing.h"

// name: LightSensing (constructor)
// function : creates an instance of LightSensing and calls begin() function.
// arguments : none
// returns : none
LightSensing::LightSensing() {
  begin();
}

// name: begin
// function : sets the pinMode of each pin and initializes the pins accordingly
// arguments : none
// returns : none
void LightSensing::begin() {
  pinMode(lightSensingLED_Red, OUTPUT);
  pinMode(lightSensingLED_Blue, OUTPUT);
  pinMode(photoTransistorLS, INPUT);
}

// name: initPins
// function : initializes the pins to aid in the LightSensing functionality
// arguments : none
// returns : none
void LightSensing::initPins() {
}

// name: readPhotoTransistorValue
// function : takes reading from phototransistor and inserts into a circular buffer
// arguments : none
// returns : none
void LightSensing::readPhotoTransistorValue() {
  // photoTransistorValue = analogRead(photoTransistor_LS);
  // int tempValue = circularBuffer[bufferIndex];
  // circularBuffer[bufferIndex++] = photoTransistorValue;
  // runningSum = runningSum - tempValue + photoTransistorValue;
  // average = runningSum/cBuff;
  // if (bufferIndex == cBuff){
  //   bufferIndex = 0;
  // }
  // Serial.print("Value: ");
  // Serial.println(photoTransistorValue);
  // Serial.print("Average: ");
  // Serial.println(average);


  digitalWrite(lightSensingLED_Red, HIGH);
  digitalWrite(lightSensingLED_Blue, LOW);
  delay(40);
  photoTransistorRed = analogRead(photoTransistorLS);
  int tempValueRed = circularBufferRed[bufferIndexRed];
  circularBufferRed[bufferIndexRed++] = photoTransistorRed;
  runningSumRed = runningSumRed - tempValueRed + photoTransistorRed;
  averageRed = runningSumRed / cBuff;
  if (bufferIndexRed == cBuff) {
    bufferIndexRed = 0;
  }

  // Serial.print("Red AnalogRead: ");
  // Serial.println(averageRed);
  // Serial.println(photoTransistorRed);
  // Serial.println("");
  // Serial.println("----------------");

  delay(40);

  digitalWrite(lightSensingLED_Red, LOW);
  digitalWrite(lightSensingLED_Blue, HIGH);
  delay(40);
  photoTransistorBlue = analogRead(photoTransistorLS);
  int tempValueBlue = circularBufferBlue[bufferIndexBlue];
  circularBufferBlue[bufferIndexBlue++] = photoTransistorBlue;
  runningSumBlue = runningSumBlue - tempValueBlue + photoTransistorBlue;
  averageBlue = runningSumBlue / cBuff;
  if (bufferIndexBlue == cBuff) {
    bufferIndexBlue = 0;
  }
  // Serial.print("Blue AnalogRead: ");
  // Serial.println(averageBlue);
  // //Serial.println(photoTransistorBlue);
  // Serial.println("");
  delay(40);
}

// name: checkColor
// function : handles logic for when circularBuffer reading falls into a certain range (depending on what color)
// arguments : none
// returns : none
int LightSensing::checkColor() {
  //BLACK = 1
  //BLUE = 2
  //RED = 3
  //YELLOW = 4
  //UNKNOWN = 5

  // if (photoTransistorRed > photoTransistorRed_Black_Min and photoTransistorRed < photoTransistorRed_Black_Max and photoTransistorBlue > photoTransistorBlue_Black_Min and photoTransistorBlue < photoTransistorBlue_Black_Max){
  //   color = 1;
  // } else if (photoTransistorRed > photoTransistorRed_Blue_Min and photoTransistorRed < photoTransistorRed_Blue_Max and photoTransistorBlue > photoTransistorBlue_Blue_Min and photoTransistorBlue < photoTransistorBlue_Blue_Max){
  //   color = 2;
  // } else if (photoTransistorRed > photoTransistorRed_Red_Min and photoTransistorRed < photoTransistorRed_Red_Max and photoTransistorBlue > photoTransistorBlue_Red_Min and photoTransistorBlue < photoTransistorBlue_Red_Max){
  //   color = 3;
  // } else if (photoTransistorRed > photoTransistorRed_Yellow_Min and photoTransistorRed < photoTransistorRed_Yellow_Max and photoTransistorBlue > photoTransistorBlue_Yellow_Min and photoTransistorBlue < photoTransistorBlue_Yellow_Max){
  //   color = 4;
  // } else {
  //   color = 5;
  // }

  if (averageRed > photoTransistorRed_Yellow_Min and averageRed < photoTransistorRed_Yellow_Max and averageBlue > photoTransistorBlue_Yellow_Min and averageBlue < photoTransistorBlue_Yellow_Max) {
    color = 4;
  } else if (averageRed > photoTransistorRed_Red_Min and averageRed < photoTransistorRed_Red_Max and averageBlue > photoTransistorBlue_Red_Min and averageBlue < photoTransistorBlue_Red_Max) {
    color = 3;
  } else if (averageRed > photoTransistorRed_Blue_Min and averageRed < photoTransistorRed_Blue_Max and averageBlue > photoTransistorBlue_Blue_Min and averageBlue < photoTransistorBlue_Blue_Max) {
    color = 2;
  } else if (averageRed > photoTransistorRed_Black_Min and averageRed < photoTransistorRed_Black_Max and averageBlue > photoTransistorBlue_Black_Min and averageBlue < photoTransistorBlue_Black_Max) {
    color = 1;
  } else {
    color = 5;
  }
}
//BLACK = 1
//BLUE = 2
//RED = 3
//YELLOW = 4
//UNKNOWN = 5


int LightSensing::getColor() {
  return color;
}

bool LightSensing::getCalibrationBool() {
  return calibrationDone;
}

void LightSensing::turnOnRedLED() {
  digitalWrite(lightSensingLED_Red, HIGH);
  digitalWrite(lightSensingLED_Blue, LOW);
}

void LightSensing::turnOnBlueLED() {
  digitalWrite(lightSensingLED_Red, LOW);
  digitalWrite(lightSensingLED_Blue, HIGH);
}

void LightSensing::turnOffLED() {
  digitalWrite(lightSensingLED_Red, LOW);
  digitalWrite(lightSensingLED_Blue, LOW);
}

int LightSensing::calibrate() {
  // CALIBRATES COLOR ON RED
  turnOnRedLED();
  photoTransistorRedValue = calibrationLoop();
  photoTransistorRed_Red_Min = photoTransistorRedValue - plusMinusRed;
  photoTransistorRed_Red_Max = photoTransistorRedValue + plusMinusRed;
  photoTransistorRedValue = 0;
  delay(200);
  turnOnBlueLED();
  photoTransistorRedValue = calibrationLoop();
  photoTransistorBlue_Red_Min = photoTransistorRedValue - plusMinusRed;
  photoTransistorBlue_Red_Max = photoTransistorRedValue + plusMinusRed;
  photoTransistorRedValue = 0;
  turnOffLED();
  delay(2000);

  //CALIBRATES COLOR ON YELLOW
  turnOnRedLED();
  photoTransistorYellowValue = calibrationLoop();
  photoTransistorRed_Yellow_Min = photoTransistorYellowValue - plusMinus;
  photoTransistorRed_Yellow_Max = photoTransistorYellowValue + plusMinus;
  photoTransistorYellowValue = 0;
  delay(200);
  turnOnBlueLED();
  photoTransistorYellowValue = calibrationLoop();
  photoTransistorBlue_Yellow_Min = photoTransistorYellowValue - plusMinus;
  photoTransistorBlue_Yellow_Max = photoTransistorYellowValue + plusMinus;
  photoTransistorYellowValue = 0;
  turnOffLED();
  delay(2000);

  //CALIBRATES COLOR ON BLUE
  turnOnRedLED();
  photoTransistorBlueValue = calibrationLoop();
  photoTransistorRed_Blue_Min = photoTransistorBlueValue - plusMinusBlue;
  photoTransistorRed_Blue_Max = photoTransistorBlueValue + plusMinusBlue;
  photoTransistorBlueValue = 0;
  delay(200);
  turnOnBlueLED();
  photoTransistorBlueValue = calibrationLoop();
  photoTransistorBlue_Blue_Min = photoTransistorBlueValue - plusMinusBlue;
  photoTransistorBlue_Blue_Max = photoTransistorBlueValue + plusMinusBlue;
  photoTransistorBlueValue = 0;
  turnOffLED();
  delay(2000);

  // CALIBRATES ON BLACK
  turnOnRedLED();
  photoTransistorBlackValue = calibrationLoop();
  photoTransistorRed_Black_Min = photoTransistorBlackValue - plusMinus;
  photoTransistorRed_Black_Max = photoTransistorBlackValue + plusMinus;
  photoTransistorBlackValue = 0;
  delay(200);
  turnOnBlueLED();
  photoTransistorBlackValue = calibrationLoop();
  photoTransistorBlue_Black_Min = photoTransistorBlackValue - plusMinus;
  photoTransistorBlue_Black_Max = photoTransistorBlackValue + plusMinus;
  photoTransistorBlackValue = 0;
  turnOffLED();
  delay(2000);

  Serial.print("Red - Red Min: ");
  Serial.println(photoTransistorRed_Red_Min);
  Serial.print("Red - Red Max: ");
  Serial.println(photoTransistorRed_Red_Max);
  Serial.print("Red - Blue Min: ");
  Serial.println(photoTransistorBlue_Red_Min);
  Serial.print("Red - Blue Max: ");
  Serial.println(photoTransistorBlue_Red_Max);
  Serial.println("");

  Serial.print("Yellow - Red Min: ");
  Serial.println(photoTransistorRed_Yellow_Min);
  Serial.print("Yellow - Red Max: ");
  Serial.println(photoTransistorRed_Yellow_Max);
  Serial.print("Yellow - Blue Min: ");
  Serial.println(photoTransistorBlue_Yellow_Min);
  Serial.print("Yellow - Blue Max: ");
  Serial.println(photoTransistorBlue_Yellow_Max);
  Serial.println("");

  Serial.print("Blue - Red Min: ");
  Serial.println(photoTransistorRed_Blue_Min);
  Serial.print("Blue - Red Max: ");
  Serial.println(photoTransistorRed_Blue_Max);
  Serial.print("Blue - Blue Min: ");
  Serial.println(photoTransistorBlue_Blue_Min);
  Serial.print("Blue - Blue Max: ");
  Serial.println(photoTransistorBlue_Blue_Max);
  Serial.println("");

  Serial.print("Black - Red Min: ");
  Serial.println(photoTransistorRed_Black_Min);
  Serial.print("Black - Red Max: ");
  Serial.println(photoTransistorRed_Black_Max);
  Serial.print("Black - Blue Min: ");
  Serial.println(photoTransistorBlue_Black_Min);
  Serial.print("Black - Blue Max: ");
  Serial.println(photoTransistorBlue_Black_Max);
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  
}

int LightSensing::calibrationLoop() {
  averageValue = 0;
  photoTransistorCalibration = 0;
  for (int i = 0; i < loopNum; i++) {
    photoTransistorCalibration = analogRead(photoTransistorLS);
    // Serial.print("photoTransistorCalibration: ");
    // Serial.println(photoTransistorCalibration);
    averageValue += photoTransistorCalibration;
    // Serial.print("averageValue in Loop: ");
    // Serial.println(averageValue);
    delay(50);
  }
  // Serial.print("averageValue before division: ");
  // Serial.println(averageValue);
  averageValue = averageValue / loopNum;
  // Serial.print("averageValue: ");
  // Serial.println(averageValue);
  return averageValue;
}

int LightSensing::laneFollowing(int colorDetected, int firstColor) {
  if (firstColor == 3){                                                 // If the first color is red
    if (colorDetected == firstColor or colorDetected == 4) {
      return 5;
    } else {
      return 6;
    }
  }

  if (firstColor == 2){                                                 // If the first color is blue
    if (colorDetected == firstColor or colorDetected == 4) {
      return 6;
    } else {
      return 5;
    }
  }
}

//BLACK = 1
//BLUE = 2
//RED = 3
//YELLOW = 4
//UNKNOWN = 5