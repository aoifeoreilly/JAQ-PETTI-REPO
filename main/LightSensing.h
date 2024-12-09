/*
  WallDetection.h - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
*/

#ifndef LightSensing_h
#define LightSensing_h

#include "Arduino.h"

const int lightSensingLED_Blue = 5;
const int lightSensingLED_Red = 11;
const int photoTransistorLS = A3;
const int cBuff_LS = 3;
const int loopNum = 40;
const int plusMinus = 70;

class LightSensing
{
  public:
    LightSensing();
    void begin();
    void initPins();
    void readPhotoTransistorValue();
    int checkColor();
    int getColor();
    int calibrate();
    bool getCalibrationBool();

    void turnOnRedLED();
    void turnOnBlueLED();
    void turnOffLED();
    int calibrationLoop();
    int laneFollowing(int colorDetected);
    bool setLeftRight(bool leftRightSet);

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
    int averageValue = 0;
    int color = 5;
    int averageRed = 0;
    int averageBlue = 0;
    
    // Variables used to calibrate the Min and Max ranges of each color's PhotoTransistor Reading. 
    // Format : photoTransistor[Either Red or Blue, indicating which light is on]_[Color Bot is On]_[Min or Max]
    int photoTransistorRed_Red_Min = 0;
    int photoTransistorRed_Red_Max = 0;
    int photoTransistorBlue_Red_Min = 0;
    int photoTransistorBlue_Red_Max = 0;
    int photoTransistorRedValue = 0;

    int photoTransistorRed_Blue_Min = 0;
    int photoTransistorRed_Blue_Max = 0;
    int photoTransistorBlue_Blue_Min = 0;
    int photoTransistorBlue_Blue_Max = 0;
    int photoTransistorBlueValue = 0;

    int photoTransistorRed_Yellow_Min = 0;
    int photoTransistorRed_Yellow_Max = 0;
    int photoTransistorBlue_Yellow_Min = 0;
    int photoTransistorBlue_Yellow_Max = 0;
    int photoTransistorYellowValue = 0;

    int photoTransistorRed_Black_Min = 0;
    int photoTransistorRed_Black_Max = 0;
    int photoTransistorBlue_Black_Min = 0;
    int photoTransistorBlue_Black_Max = 0;
    int photoTransistorBlackValue = 0;
    

    int redAverage = 0;
    int blueAverage = 0;
    int photoTransistorCalibration = 0;

    bool calibrationDone = 0;
    int oldColor = 3;
    int newColor = 3;
    bool leftRight = false;
};

#endif
