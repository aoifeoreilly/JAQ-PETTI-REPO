/*
  GoBeyond.h - Library for Go Beyond code
  Created by Aoife O'Reilly, December 4th, 2024.
*/

#ifndef GoBeyond_h
#define GoBeyond_h

#include "Arduino.h"

const int leftLED = 2;
const int rightLED = 12;

class GoBeyond
{
  public:
    GoBeyond();
    void begin();
    void initPins();
    void checkColor();
    void leftLightOnlyOn();
    void rightLightOnlyOn();
    void bothLightsOn();
};

#endif