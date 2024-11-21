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
//    *. |        2A.        |        7        |         ~9         | 
//    *.  -----------------------------------------------------------
//    *. |   Enable 3 & 4    |        9        |          7         | 
//    *.  -----------------------------------------------------------
//    *. |        3A.        |       10        |         ~6         | 
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
void StateMachine::buttonStateFunctions(int buttonState) {
  Serial.println(buttonState);
  if(buttonState == 0){
    initPins();
  }
  if(buttonState == 1){ //GO FORWARD
    buttonStateResetPins();
    analogWrite(leftWheelInputA, analogWriteSpeedLeft);
    analogWrite(rightWheelInputA, analogWriteSpeedRight);

    // if(buttonState == 1){ 
   	// buttonStateResetPins();
    //   // Current time in seconds
    // float time = millis() / 1000.0;

    // // Sine wave offset as time passes
    // float sineValue = sin(2 * PI * sweepFrequency * time); // sin(ωt)

    // // Calculate the PWM values for each wheel
    // int leftPWM = analogWriteSpeed + amplitudePWM * sineValue; // vL = V+Asin(ωt)
    // int rightPWM = analogWriteSlow - amplitudePWM * sineValue; // vR = V+Asin(ωt)

    // // Apply PWM values to motors
    // analogWrite(leftWheelInputA, leftPWM);
    // analogWrite(rightWheelInputA, rightPWM);

    //   // Short delay to control loop timing
    // delay(10);

  }
  if(buttonState == 2){ //GO BACKWARDS
    buttonStateResetPins();
    analogWrite(leftWheelInputB, analogWriteSpeedReverse);
    analogWrite(rightWheelInputB, analogWriteSpeedLeft);
  }
  if(buttonState == 3){ // PIVOT CLOCKWISE
    buttonStateResetPins();
    analogWrite(leftWheelInputA, analogWriteSpeedLeft);
    analogWrite(rightWheelInputA, analogWriteSpeed2);
  }
  if(buttonState == 4){ //PIVOT COUNTERCLOCKWISE
    buttonStateResetPins();
    analogWrite(leftWheelInputA, analogWriteSpeed2);
    analogWrite(rightWheelInputA, analogWriteSpeedRight);
  }
  if(buttonState == 5){
    buttonStateResetPins();
    analogWrite(leftWheelInputA, analogWriteSpeedLeft);
    analogWrite(rightWheelInputA, analogWriteSpeed2);
    delay(2000);
    digitalWrite(leftWheelInputA, LOW);
    digitalWrite(rightWheelInputA, LOW);
  }
  if(buttonState == 6){
    buttonStateResetPins();
    analogWrite(leftWheelInputA, analogWriteSpeed2);
    analogWrite(rightWheelInputA, analogWriteSpeedRight);
    delay(2000);
    digitalWrite(leftWheelInputA, LOW);
    digitalWrite(rightWheelInputA, LOW);
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




