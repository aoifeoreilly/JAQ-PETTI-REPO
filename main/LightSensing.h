/*
  WallDetection.h - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
*/

#ifndef LightSensing_h
#define LightSensing_h

#include "Arduino.h"

const int lightSensingLED_Red = 5;
const int lightSensingLED_Blue = 11;
const int photoTransistorLS = A3;
const int cBuff_LS = 10;

class LightSensing
{
  public:
    LightSensing();
    void begin();
    void initPins();
    void readPhotoTransistorValue();
    int checkColor();
    int getColor();



  private:
    int photoTransistorValue = 0;
    int photoTransistorBlue = 0;
    int photoTransistorRed = 0;
    int runningSumRed = 0;
    int runningSumBlue = 0;
    int circularBufferResult;
    int circularBufferRed[cBuff_LS];
    int circularBufferBlue[cBuff_LS];
    int bufferIndexRed = 0;
    int bufferIndexBlue = 0;
    int averageRed = 0;
    int averageBlue = 0;
    int color = 5;
};

#endif
