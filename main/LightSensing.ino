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
LightSensing::LightSensing(){
  begin();
}

// name: begin
// function : sets the pinMode of each pin and initializes the pins accordingly
// arguments : none
// returns : none
void LightSensing::begin(){
  // pinMode(lightSensingLED_Red, OUTPUT);
  // pinMode(lightSensingLED_Blue, OUTPUT);
  // pinMode(lightSensingLEDS, OUTPUT);
  // pinMode(photoTransistor, INPUT);
  // initPins();
}

// name: initPins
// function : initializes the pins to aid in the LightSensing functionality
// arguments : none
// returns : none
void LightSensing::initPins(){
  //digitalWrite(lightSensingLEDS, HIGH);
}

// name: readPhotoTransistorValue
// function : takes reading from phototransistor and inserts into a circular buffer
// arguments : none
// returns : none
void LightSensing::readPhotoTransistorValue(){
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
}

// name: checkColor
// function : handles logic for when circularBuffer reading falls into a certain range (depending on what color)
// arguments : none
// returns : none
void LightSensing::checkColor(){

}
