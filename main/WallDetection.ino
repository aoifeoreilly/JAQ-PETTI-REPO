/*
  WallDetection.cpp - Library for Wall Detection code.
  Created by Quan Vu, October 8, 2024.
*/

#include "Arduino.h"
#include "WallDetection.h"

// name: WallDetection (constructor)
// function : creates an instance of WallDetection and calls begin() function.
// arguments : none
// returns : none
WallDetection::WallDetection() {
  begin();
}

// name: begin
// function : sets the pinMode of each pin and initializes the pins accordingly
// arguments : none
// returns : none
void WallDetection::begin() {
  pinMode(wallLED, OUTPUT);
  pinMode(photoTransistor, INPUT);
  initPins();
}

// name: initPins
// function : initializes the pins to aid in the WallDetection functionality
// arguments : none
// returns : none
void WallDetection::initPins() {
  digitalWrite(wallLED, HIGH);
}

// name: readPhotoTransistorValue
// function : takes reading from phototransistor and inserts into a circular buffer
// arguments : none
// returns : none
void WallDetection::readPhotoTransistorValue() {
  photoTransistorValue = analogRead(photoTransistor);
  int tempValue = circularBuffer[bufferIndex];
  circularBuffer[bufferIndex++] = photoTransistorValue;
  runningSum = runningSum - tempValue + photoTransistorValue;
  average = runningSum/cBuff;
  if (bufferIndex == cBuff){
    bufferIndex = 0;
  }

  // client.beginMessage(TYPE_TEXT);
  // client.print(average);
  // client.endMessage();
  // Serial.println(average);
  // Serial.println(photoTransistorValue);
}

// name: checkWall
// function : handles logic for when circularBuffer reading becomes lower than a constant wallVoltage (we choose)
// arguments : none
// returns : none
void WallDetection::checkWall() {

// const int wallVoltageWall1 = 580;
// const int wallVoltageWall2 = 640;
// const int wallVoltageWall3 = 575;
// const int wallVoltageWall4 = 620;

  // if ((photoTransistorValue < wallVoltageWall1 + plusMinusWD and photoTransistorValue > wallVoltageWall1 - plusMinusWD) and (wallNum == 1) and (wallDetected == false)){
  //     Serial.println("STOP: WALL DETECTED");
  //     wallDetected = true;
  //     wallNum += 1;
  // }
  // else if ((photoTransistorValue < wallVoltageWall2 + plusMinusWD and photoTransistorValue > wallVoltageWall2 - plusMinusWD) and (wallNum == 2) and (wallDetected == false)){
  //     Serial.println("STOP: WALL DETECTED");
  //     wallDetected = true;
  //     wallNum += 1;
  // }
  // else if ((photoTransistorValue < wallVoltageWall3 + plusMinusWD and photoTransistorValue > wallVoltageWall3 - plusMinusWD) and (wallNum == 3) and (wallDetected == false)){
  //     Serial.println("STOP: WALL DETECTED");
  //     wallDetected = true;
  //     wallNum += 1;
  // }
  // else if ((photoTransistorValue < wallVoltageWall4 + plusMinusWD and photoTransistorValue > wallVoltageWall4 - plusMinusWD) and (wallNum == 4) and (wallDetected == false)){
  //     Serial.println("STOP: WALL DETECTED");
  //     wallDetected = true;
  //     wallNum += 1;
  // }
  // else {
  //   wallDetected = false;
  // }

  if(average < wallVoltageInt){
    Serial.println("STOP: WALL DETECTED");
    wallDetected = true;
  } else {
    wallDetected = false;
  }
  // Serial.println(wallNum);
}

// name: getWallDetectedBool
// function : getter indicating whether or not a wall was detected
// arguments : none
// returns : none
bool WallDetection::getWallDetectedBool() {
  return wallDetected;
}

int WallDetection::setWallNum(int WallNum){
  wallNum = WallNum;
}
