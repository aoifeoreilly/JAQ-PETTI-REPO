/*
  StateMachine.h - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
*/


#ifndef StateMachine_h
#define StateMachine_h

#include "Arduino.h"


const int enableLeftWheel = 13;
const int leftWheelInputA = 10;
const int leftWheelInputB = 9;
const int enableRightWheel = 7;
const int rightWheelInputA = 6;
const int rightWheelInputB = 3;
const int buttonPin = 5;     // the number of the pushbutton pin
const int analogWriteSpeed = 200;
const int analogWriteSpeed2 = 40;

class StateMachine
{
  public:
    StateMachine();
    void begin();
    void initPins();
    void buttonStateFunctions(int buttonState);
    void loop();
    //static void pin_ISR();
  private:
    volatile int buttonState = 0;         // variable for reading the pushbutton status
    volatile bool buttonPressed = false;  // flag to indicate if the button was pressed
};

#endif
