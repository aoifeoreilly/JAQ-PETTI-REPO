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
  pinMode(photoTransistorLS, INPUT);
}

// name: initPins
// function : initializes the pins to aid in the LightSensing functionality
// arguments : none
// returns : none
void LightSensing::initPins(){
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
  delay(80);
  photoTransistorRed = analogRead(photoTransistorLS);
  int tempValueRed = circularBufferRed[bufferIndexRed];
  circularBufferRed[bufferIndexRed++] = photoTransistorRed;
  runningSumRed = runningSumRed - tempValueRed + photoTransistorRed;
  averageRed = runningSumRed/cBuff;
  if(bufferIndexRed == cBuff){
    bufferIndexRed = 0;
  }
  Serial.print("Red AnalogRead: ");
  Serial.print(photoTransistorRed);
  Serial.println("----------------");
  Serial.println(" ");

  delay(80);

  digitalWrite(lightSensingLED_Red, LOW);
  digitalWrite(lightSensingLED_Blue, HIGH);
  delay(80);
  photoTransistorBlue = analogRead(photoTransistorLS);
  int tempValueBlue = circularBufferBlue[bufferIndexBlue];
  circularBufferBlue[bufferIndexBlue++] = photoTransistorBlue;
  runningSumBlue = runningSumBlue - tempValueBlue + photoTransistorBlue;
  averageBlue = runningSumBlue/cBuff;
  if(bufferIndexBlue == cBuff){
    bufferIndexBlue = 0;
  }
  Serial.print("Blue AnalogRead: ");
  Serial.println(photoTransistorBlue);
  delay(80);

}

// name: checkColor
// function : handles logic for when circularBuffer reading falls into a certain range (depending on what color)
// arguments : none
// returns : none
int LightSensing::checkColor(){
  //BLACK = 1
  //BLUE = 2
  //RED = 3
  //YELLOW = 4
  //UNKNOWN = 5

  // if(photoTransistorBlue > 340 and photoTransistorBlue < 390){
  //   color = 2;
  // } else if (photoTransistorRed > 300 and photoTransistorBlue < 250) {
  //   color = 3;
  // } else if (photoTransistorBlue < 190){
  //   color = 4;
  // } else if (photoTransistorRed > 500) {
  //   color = 1;
  // } else {
  //   color = 5;
  // }
  if (photoTransistorRed < 210 and photoTransistorRed < 210){
    color = 4;
  } else if(photoTransistorBlue < 340 and photoTransistorRed < 340){
    color = 2;
  } else if (photoTransistorRed > 300 and photoTransistorBlue < 250) {
    color = 3;
  } else if (photoTransistorBlue > 350 and photoTransistorRed > 350) {
    color = 1;
  } else {
    color = 5;
  }

  // if(photoTransistorBlue > 420 and photoTransistorRed < 275){
  //   color = 2;
  // } else if (photoTransistorBlue < 275 and photoTransistorBlue > 230){
  //   color = 3;
  // } else if (photoTransistorBlue < 200 and photoTransistorRed < 200){
  //   color = 4;
  // } else if (photoTransistorBlue > 500) {
  //   color = 1;
  // } else {
  //   color = 5;
  // }
  // Serial.print("Color: ");
  // Serial.println(color);
}

int LightSensing::getColor(){
  return color;
}