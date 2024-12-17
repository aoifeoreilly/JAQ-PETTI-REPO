/*
  WallDetection.h - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
*/

#ifndef WallDetection_h
#define WallDetection_h

#include "Arduino.h"

const int cBuff = 2;
const int wallVoltageInt = 735;
const int wallVoltageWall1 = 615;
const int wallVoltageWall2 = 620;
const int wallVoltageWall3 = 620;
const int wallVoltageWall4 = 630;

const int plusMinusWD = 5;
const int voltageInt = 0;
const int wallLED = 0;
const int photoTransistor = A2;

class WallDetection
{
  public:
    WallDetection();
    void begin();
    void initPins();
    void readPhotoTransistorValue();
    void checkWall();
    bool getWallDetectedBool();
    int WallDetection::setWallNum(int WallNum);
    
  private:
    int photoTransistorValue = 0;
    int runningSum = 0;
    int circularBufferResult;
    int circularBuffer[cBuff];
    int bufferIndex = 0;
    int average = 250;
    int wallNum = 1;
    bool wallDetected = false; 
};

#endif
