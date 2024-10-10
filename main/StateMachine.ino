/*
  StateMachine.cpp - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
*/

#include "Arduino.h"
#include "StateMachine.h"

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
  //attachInterrupt(digitalPinToInterrupt(buttonPin), pin_ISR, FALLING);
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


// const int enableLeftWheel = 13;
// const int leftWheelInputA = 10;
// const int leftWheelInputB = 9;
// const int enableRightWheel = 7;
// const int rightWheelInputA = 6;
// const int rightWheelInputB = 3;
// const int buttonPin = 5;     // the number of the pushbutton pin
// const int analogWriteSpeed = 200;
// const int analogWriteSpeed2 = 40;


// // variables will change:
// volatile int buttonState = 0;         // variable for reading the pushbutton status
// volatile bool buttonPressed = false;  // flag to indicate if the button was pressed


// // name: setup
// // function : serves as the setup of the arduino, enabling all pins and initializing as needed
// // arguments : none
// // returns : none
// void setup() {
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
//   pinMode(enableLeftWheel, OUTPUT);
//   pinMode(leftWheelInputA, OUTPUT);
//   pinMode(leftWheelInputB, OUTPUT); 
//   pinMode(enableRightWheel, OUTPUT);
//   pinMode(rightWheelInputA, OUTPUT);
//   pinMode(rightWheelInputB, OUTPUT);
//   pinMode(buttonPin, INPUT);
//   Serial.begin(9600);
//   initPins();
//   attachInterrupt(digitalPinToInterrupt(buttonPin), pin_ISR, FALLING);
// }

// // name: initPins
// // function : initializes all the pins (runs in setup at the start)
// // arguments : none
// // returns : none
// void initPins(){
//   digitalWrite(enableLeftWheel, LOW);
//   digitalWrite(leftWheelInputA, LOW);
//   digitalWrite(leftWheelInputB, LOW);
//   digitalWrite(enableRightWheel, LOW);
//   digitalWrite(rightWheelInputA, LOW);
//   digitalWrite(rightWheelInputB, LOW);  
// }

// name: loop
// function : the main function that runs for as long as the Arduino is on (loops forever)
// arguments : none
// returns : none
void StateMachine::loop() {
  if (buttonPressed) {
    if (!digitalRead(buttonPin)) {
      buttonState += 1;
    }
    if (buttonState > 6) {
      buttonState = 0;
    }

    Serial.println(buttonState);      //Printing for testing
    buttonStateFunctions(buttonState);
    // Reset the flag
    buttonPressed = false;
  }
  delay(1);
}

// name: buttonStateFunctions
// function : conditionals that run based on the current buttonState
// arguments : buttonState (the current button state from 0 to 6)
// returns : none
void StateMachine::buttonStateFunctions(int buttonState) {
  if(buttonState == 0){
    initPins();
  }
  if(buttonState == 1){ //GO FORWARD
    digitalWrite(enableRightWheel, HIGH);
    digitalWrite(enableLeftWheel, HIGH);
    digitalWrite(leftWheelInputB, LOW);
    digitalWrite(rightWheelInputB, LOW);
    analogWrite(leftWheelInputA, analogWriteSpeed);
    analogWrite(rightWheelInputA, analogWriteSpeed);
    delay(1000); //wait for a second      
  }
  if(buttonState == 2){ //GO BACKWARDS
    digitalWrite(enableRightWheel, HIGH);
    digitalWrite(enableLeftWheel, HIGH);
    digitalWrite(leftWheelInputA, LOW);
    digitalWrite(rightWheelInputA, LOW);
    analogWrite(leftWheelInputB, analogWriteSpeed);
    analogWrite(rightWheelInputB, analogWriteSpeed);
    delay(1000); //wait for a second
  }
  if(buttonState == 3){ // PIVOT CLOCKWISE
    digitalWrite(enableRightWheel, HIGH);
    digitalWrite(enableLeftWheel, HIGH);
    digitalWrite(leftWheelInputB, LOW);
    digitalWrite(rightWheelInputB, LOW);
    analogWrite(leftWheelInputA, analogWriteSpeed);
    analogWrite(rightWheelInputA, analogWriteSpeed2);
    digitalWrite(enableRightWheel, HIGH);
    // digitalWrite(enableLeftWheel, HIGH);
    // digitalWrite(leftWheelInputB, LOW);
    // digitalWrite(rightWheelInputA, LOW);
    // analogWrite(leftWheelInputA, analogWriteSpeed);
    // analogWrite(rightWheelInputB, analogWriteSpeed2);

  }
  if(buttonState == 4){ //PIVOT COUNTERCLOCKWISE
    digitalWrite(enableRightWheel, HIGH);
    digitalWrite(enableLeftWheel, HIGH);
    digitalWrite(leftWheelInputB, LOW);
    digitalWrite(rightWheelInputB, LOW);
    analogWrite(leftWheelInputA, analogWriteSpeed2);
    analogWrite(rightWheelInputA, analogWriteSpeed);
  }
  if(buttonState == 5){
    digitalWrite(enableRightWheel, HIGH);
    digitalWrite(enableLeftWheel, HIGH);
    digitalWrite(leftWheelInputB, LOW);
    digitalWrite(rightWheelInputB, LOW);
    analogWrite(leftWheelInputA, analogWriteSpeed);
    analogWrite(rightWheelInputA, analogWriteSpeed2);
    delay(2000);
    digitalWrite(leftWheelInputA, LOW);
    digitalWrite(rightWheelInputA, LOW);
  }
  if(buttonState == 6){
    digitalWrite(enableRightWheel, HIGH);
    digitalWrite(enableLeftWheel, HIGH);
    digitalWrite(leftWheelInputB, LOW);
    digitalWrite(rightWheelInputB, LOW);
    analogWrite(leftWheelInputA, analogWriteSpeed2);
    analogWrite(rightWheelInputA, analogWriteSpeed);
    delay(2000);
    digitalWrite(leftWheelInputA, LOW);
    digitalWrite(rightWheelInputA, LOW);
  }
}

// name: pin_ISR
// function : an interrupt that triggers everytime the button is pressed
// arguments : none
// returns : none
// void StateMachine::pin_ISR() {
//   buttonPressed = true;       // Set flag to true when interrupt triggers
// }



