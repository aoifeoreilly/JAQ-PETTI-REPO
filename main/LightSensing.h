/*
  WallDetection.h - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
*/

#ifndef LightSensing_h
#define LightSensing_h

#include "Arduino.h"

const int lightSensingLEDS = 10; // ALL LIGHTS CAN BE POWERED USING ONE PIN
const int photoTransistor_LS = A2;

class LightSensing
{
  public:
    LightSensing();
    void begin();
    void initPins();



  private:
    int photoTransistorValue = 0;

};

#endif
