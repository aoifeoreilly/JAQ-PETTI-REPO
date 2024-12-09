/*
  StateMachine.cpp - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
*/

#include "Arduino.h"
#include "StateMachine.h"

// name: StateMachine (constructor)
// function : creates an instance of StateMachine and calls begin() function.
// arguments : none
// returns : none
StateMachine::StateMachine() {
  begin();
}

//   /*
//    *.  -----------------------------------------------------------
//    *. | L293 Pin Function | L293 Pin Number | Arduino Pin Number |
//    *.  -----------------------------------------------------------
//    *. |   Enable 1 & 2    |        1        |         13         | 
//    *.  -----------------------------------------------------------
//    *. |        1A.        |        2        |        ~10         | 
//    *.  -----------------------------------------------------------
//    *. |        2A.        |        7        |         ~6         | 
//    *.  -----------------------------------------------------------
//    *. |   Enable 3 & 4    |        9        |          7         | 
//    *.  -----------------------------------------------------------
//    *. |        3A.        |       10        |         ~9         | 
//    *.  -----------------------------------------------------------
//    *. |        4A.        |       15        |         ~3         | 
//    *.  -----------------------------------------------------------
//    *. |    PUSHBUTTON     |       NA        |          5         | 
//    *.  -----------------------------------------------------------
//    */

// name: begin
// function : serves as the setup of the state machine, enabling all pins and initializing as needed
// arguments : none
// returns : none
void StateMachine::begin() {
  pinMode(enableLeftWheel, OUTPUT);
  pinMode(leftWheelInputA, OUTPUT);
  pinMode(leftWheelInputB, OUTPUT); 
  pinMode(enableRightWheel, OUTPUT);
  pinMode(rightWheelInputA, OUTPUT);
  pinMode(rightWheelInputB, OUTPUT);
  pinMode(buttonPin, INPUT);
  initPins();
}

// name: initPins
// function : initializes all the pins (runs in setup at the start)
// arguments : none
// returns : none
void StateMachine::initPins() {
  digitalWrite(enableLeftWheel, LOW);
  digitalWrite(leftWheelInputA, LOW);
  digitalWrite(leftWheelInputB, LOW);
  digitalWrite(enableRightWheel, LOW);
  digitalWrite(rightWheelInputA, LOW);
  digitalWrite(rightWheelInputB, LOW);  
}

// name: buttonStateFunctions
// function : conditionals that run based on the current buttonState
// arguments : buttonState (the current button state from 0 to 6)
// returns : none
void StateMachine::buttonStateFunctions() {
  //Serial.println(buttonState);
  if(buttonState == 0){
    initPins();
  }
  if(buttonState == 1){ //GO FORWARD
    buttonStateResetPins();
    analogWrite(leftWheelInputA, analogWriteSpeedLeft);
    analogWrite(rightWheelInputA, analogWriteSpeedRight);
  }
  if(buttonState == 2){ //GO BACKWARDS
    buttonStateResetPins();
    analogWrite(leftWheelInputB, analogWriteSpeedLeft);
    analogWrite(rightWheelInputB, analogWriteSpeedRight);
  }
  if(buttonState == 3){ // PIVOT COUNTERCLOCKWISE
    buttonStateResetPins();
    analogWrite(leftWheelInputA, analogWriteSpeedLeft);
    analogWrite(rightWheelInputB, analogWriteSpeedTurn);
  }
  if(buttonState == 4){ //PIVOT CLOCKWISE
    buttonStateResetPins();
    analogWrite(leftWheelInputB, analogWriteSpeedTurn);
    analogWrite(rightWheelInputA, analogWriteSpeedRight);
  }
  if(buttonState == 5){ // TURN LEFT
    buttonStateResetPins();
    analogWrite(leftWheelInputA, analogWriteSpeedLeft);
    analogWrite(rightWheelInputA, analogWriteSpeedRadiusTurn);
  }
  if(buttonState == 6){ // TURN RIGHT
    buttonStateResetPins();
    analogWrite(leftWheelInputA, analogWriteSpeedRadiusTurn);
    analogWrite(rightWheelInputA, analogWriteSpeedRight);
  }
}

// name: buttonStateResetPins
// function : sets enable pins to high and all other motor functionality to low
// arguments : none
// returns : none
void StateMachine::buttonStateResetPins() {
    digitalWrite(enableRightWheel, HIGH);
    digitalWrite(enableLeftWheel, HIGH);
    digitalWrite(leftWheelInputA, LOW);
    digitalWrite(rightWheelInputA, LOW);
    digitalWrite(leftWheelInputB, LOW);
    digitalWrite(rightWheelInputB, LOW);
}

void StateMachine::buttonStateSetter(int bState){
  buttonState = bState;
}




