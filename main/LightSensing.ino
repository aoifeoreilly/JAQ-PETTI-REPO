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
  
}
// const int wallVoltageInt = 0;
// const int voltageInt = 0;
// const int redLed = 12;
// const int blueLed = 11;
// const int photoTransistor = A2;

// void setup() {
//   pinMode(redLed, OUTPUT);
//   pinMode(blueLed, OUTPUT);
//   pinMode(photoTransistor, INPUT);
//   Serial.begin(9600);
//   initPins();
// }

// void loop() {
//   digitalWrite(blueLed, LOW);  
//   digitalWrite(redLed, HIGH);
//   delay(1000);

//   digitalWrite(redLed, LOW);
//   digitalWrite(blueLed, HIGH);
//   delay(1000);
// }

// void initPins(){
//   digitalWrite(redLed, LOW);
//   digitalWrite(blueLed, LOW);
// }