/*
  WallDetection.h - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
*/

#ifndef LightSensing_h
#define LightSensing_h

#include "Arduino.h"

const int lightSensingLEDS = 10; // ALL LIGHTS CAN BE POWERED USING ONE PIN
const int lightSensingLED_Red = 5;
const int lightSensingLED_Blue = 11;
const int photoTransistorLS = A4;
const int cBuff_LS = 5;
volatile int photoTransistorReading = 0;

class LightSensing
{
  public:
    LightSensing();
    void begin();
    void initPins();
    void readPhotoTransistorValue();
    void checkColor();



  private:
    int photoTransistorValue = 0;
    int runningSum = 0;
    int circularBufferResult;
    int circularBuffer[cBuff_LS];
    int bufferIndex = 0;
    int average = 500;

};

#endif
