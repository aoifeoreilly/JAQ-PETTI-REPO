/*
  GoBeyond.h - Library for Go Beyond code
  Created by Aoife O'Reilly, December 4th, 2024.
*/

#ifndef GoBeyond_h
#define GoBeyond_h

#include "Arduino.h"

const int leftLED = 12;
const int rightLED = 2;

class GoBeyond
{
  public:
    GoBeyond();
    void begin();
    void checkColor();
    void leftLightOnlyOn();
    void rightLightOnlyOn();
    void bothLightsOn();
    void bothLightsOff();
    void turnDirection(int turnNum);
};

#endif