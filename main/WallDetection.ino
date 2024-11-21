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
  //Serial.println(average);
}

// name: checkWall
// function : handles logic for when circularBuffer reading becomes lower than a constant wallVoltage (we choose)
// arguments : none
// returns : none
void WallDetection::checkWall() {
  if (average < wallVoltageInt){
      //Serial.println("STOP: WALL DETECTED");
  }
}

