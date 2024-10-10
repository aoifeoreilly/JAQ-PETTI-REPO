/*
  WallDetection.cpp - Library for Wall Detection code.
  Created by Quan Vu, October 8, 2024.
*/

#include "Arduino.h"
#include "WallDetection.h"

WallDetection::WallDetection() {
  begin();
}

void WallDetection::begin() {
  pinMode(wallLED, OUTPUT);
  pinMode(photoTransistor, INPUT);
  initPins();
}

void WallDetection::initPins() {
  digitalWrite(wallLED, HIGH);
}

void WallDetection::checkWall() {
  photoTransistorValue = analogRead(photoTransistor);
  int tempValue = circularBuffer[bufferIndex];
  circularBuffer[bufferIndex++] = photoTransistorValue;
  runningSum = runningSum - tempValue + photoTransistorValue;
  average = runningSum/cBuff;
  if (bufferIndex == cBuff){
    bufferIndex = 0;
  }
  Serial.print("Value: ");
  Serial.println(photoTransistorValue);
  Serial.print("Average: ");
  Serial.println(average);

  if (average > wallVoltageInt){
      // Write Code to Reverse
  }

  delay(200);
}














// const int wallVoltageInt = 0;
// const int voltageInt = 0;
// const int wallLed = 0;
// const int redLed = 0;
// const int blueLed = 0;
// const int photoTransistor = A1;

// const uint8_t cBuff = 5;
// volatile int runningSum = 0;
// volatile int circularBufferResult; // CIRCULAR BUFFER 
// int circularBuffer[cBuff];
// int buffer_index = 0;
// int average = 250;

// volatile int photoTransistorValue = 0;

// void setup() {
//   pinMode(wallLed, OUTPUT);
//   pinMode(redLed, OUTPUT);
//   pinMode(blueLed, OUTPUT);
//   pinMode(photoTransistor, INPUT);
//   Serial.begin(9600);
//   initPins();
// }

// void loop() {
  // photoTransistorValue = analogRead(photoTransistor);
  // int tempValue = circularBuffer[buffer_index];
  // circularBuffer[buffer_index++] = photoTransistorValue;
  // runningSum = runningSum - tempValue + photoTransistorValue;
  // average = runningSum/cBuff;
  // if (buffer_index == cBuff){
  //   buffer_index = 0;
  // }
  // Serial.print("Value: ");
  // Serial.println(photoTransistorValue);
  // Serial.print("Average: ");
  // Serial.println(average);

  // if (average > wallVoltageInt){
  //     // Write Code to Reverse
  // }

  // delay(200);
// }

