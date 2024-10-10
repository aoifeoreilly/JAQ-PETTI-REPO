/*
  WallDetection.h - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
*/
#include "Arduino.h"
#include "LightSensing.h"

LightSensing::LightSensing(){
  begin();
}

void LightSensing::begin(){
  pinMode(lightSensingLEDS, OUTPUT);
  pinMode(photoTransistor, INPUT);
  initPins();
}

void LightSensing::initPins(){
  digitalWrite(lightSensingLEDS, HIGH);
}

void LightSensing::readPhotoTransistorValue(){
  photoTransistorValue = analogRead(photoTransistor_LS);
  int tempValue = circularBuffer[bufferIndex];
  circularBuffer[bufferIndex++] = photoTransistorValue;
  runningSum = runningSum - tempValue + photoTransistorValue;
  average = runningSum/cBuff;
  if (bufferIndex == cBuff){
    bufferIndex = 0;
  }
  // Serial.print("Value: ");
  // Serial.println(photoTransistorValue);
  // Serial.print("Average: ");
  Serial.println(average);
}

void LightSensing::checkColor(){
  if (average > 0 && average < 200) {
    Serial.println("On Yellow Surface");
  } else if (average > 200 && average < 360){
    Serial.println("On Blue Surface");
  } else if (average > 360 && average < 480) {
    Serial.println("On Red Surface");
  } else {
    Serial.println("On Black Surface");
  }
}