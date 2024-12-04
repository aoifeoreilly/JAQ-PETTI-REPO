/*
  WallDetection.h - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
*/

#ifndef WallDetection_h
#define WallDetection_h

#include "Arduino.h"

const int cBuff = 5;
const int wallVoltageInt = 960;
const int voltageInt = 0;
const int wallLED = 0;
const int photoTransistor = A1;

class WallDetection
{
  public:
    WallDetection();
    void begin();
    void initPins();
    void readPhotoTransistorValue();
    void checkWall();
    bool getWallDetectedBool();
    
  private:
    int photoTransistorValue = 0;
    int runningSum = 0;
    int circularBufferResult;
    int circularBuffer[cBuff];
    int bufferIndex = 0;
    int average = 250;
    bool wallDetected = false; 
};

#endif
