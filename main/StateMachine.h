/*
  StateMachine.h - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
*/


#ifndef StateMachine_h
#define StateMachine_h

#include "Arduino.h"


const int enableLeftWheel = 13;
const int leftWheelInputA = 10;
const int leftWheelInputB = 6;
const int enableRightWheel = 7;
const int rightWheelInputA = 9;
const int rightWheelInputB = 3;
const int buttonPin = 5;     // the number of the pushbutton pin
// const int analogWriteSpeedLeft = 125;
// const int analogWriteSpeedRight = 130;
// const int analogWriteSpeedReverse = 127;
// const int analogWriteSpeedTurn = 90;
// const int analogWriteSpeedRadiusTurn = 60;

// const int analogWriteSpeedLeft = 135;
// const int analogWriteSpeedRight = 125;
// const int analogWriteSpeedReverse = 130;
// const int analogWriteSpeedTurn = 90;
// const int analogWriteSpeedRadiusTurn = 60;

const int analogWriteSpeedLeft = 120;
const int analogWriteSpeedRight = 120;
const int analogWriteSpeedReverse = 120;
const int analogWriteSpeedTurn = 75;
const int analogWriteSpeedRadiusTurn = 65;

// Constants Used for Sweeping Logic
const int analogWriteSpeed2 = 40;
const int analogWriteSpeedTest = 230;
const int analogWriteSpeedTest2 = 40;
const int amplitudePWM = 50;  	    // A
const float sweepFrequency = 0.5; // f = 2pi/w = 0.5  


class StateMachine
{
  public:
    StateMachine();
    void begin();
    void initPins();
    void buttonStateFunctions();
    void buttonStateResetPins();
    void buttonStateSetter(int bState);
  private:
    volatile int buttonState = 0;         // variable for reading the pushbutton status
};

#endif
