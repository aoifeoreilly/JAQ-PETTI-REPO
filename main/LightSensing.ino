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
  pinMode(lightSensingLED_Red, OUTPUT);
  pinMode(lightSensingLED_Blue, OUTPUT);
  pinMode(lightSensingLEDS, OUTPUT);
  pinMode(photoTransistorLS, INPUT);
  //initPins();
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
  digitalWrite(lightSensingLED_Red, HIGH);
  digitalWrite(lightSensingLED_Blue, LOW);
  photoTransistorReading = analogRead(photoTransistorLS);
  Serial.print("Red AnalogRead: ");
  Serial.print(photoTransistorReading);
  Serial.println("----------------");
  Serial.println(" ");

  delay(500);
  digitalWrite(lightSensingLED_Red, LOW);
  digitalWrite(lightSensingLED_Blue, HIGH);
  photoTransistorReading = analogRead(photoTransistorLS);
  Serial.print("Blue AnalogRead: ");
  Serial.println(photoTransistorReading);
  Serial.println(" ");

}

// name: checkColor
// function : handles logic for when circularBuffer reading falls into a certain range (depending on what color)
// arguments : none
// returns : none
void LightSensing::checkColor(){

}

// const int lightSensingLED_Red = 2;
// const int lightSensingLED_Blue = 4;
// const int photoTransistor = A4;
// volatile int photoTransistorReading = 0;

// void setup() {
//   Serial.begin(9600);
//   pinMode(lightSensingLED_Red, OUTPUT);
//   pinMode(lightSensingLED_Blue, OUTPUT);
//   pinMode(photoTransistor, INPUT);
// }

// void loop() {
//   digitalWrite(lightSensingLED_Red, HIGH);
//   digitalWrite(lightSensingLED_Blue, LOW);
//   photoTransistorReading = analogRead(photoTransistor);
//   Serial.print("Red AnalogRead: ");
//   Serial.print(photoTransistorReading);
//   Serial.println("----------------");
//   Serial.println(" ");

//   delay(500);
//   digitalWrite(lightSensingLED_Red, LOW);
//   digitalWrite(lightSensingLED_Blue, HIGH);
//   photoTransistorReading = analogRead(photoTransistor);
//   Serial.print("Blue AnalogRead: ");
//   Serial.println(photoTransistorReading);
//   Serial.println(" ");

//   delay(500);
// }

