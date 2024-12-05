/*
  main.cpp - Library for main fuctionality code.
  Created by Quan Vu, October 8, 2024.
*/

#include "Arduino.h"
#include "WallDetection.h"
#include "StateMachine.h"
#include "LightSensing.h"
#include "WebSocket.h"
#include "BatteryDetection.h"

// Declaration of Each Component
WallDetection wall;
StateMachine state;
LightSensing ls;
WebSocket ws;
BatteryDetection bd;

volatile int stateMachine = 0;
volatile int stateNum = 0;
volatile int previousStateNum = 0;
String state0 = "State 0";
String state1 = "State 1";
String state2 = "State 2";
String state3 = "State 3";
String state4 = "State 4";
String state5 = "State 5";
String state6 = "State 6";


// name: setup
// function : serves as the setup of the arduino, enabling all pins 
//            and initializing inputs and outputs of each component as needed
// arguments : none
// returns : none
void setup() {
  Serial.begin(9600);
  wall.begin();
  state.begin();
  ls.begin();
  ws.begin();
  bd.begin();
}

// name: loop
// function : main function that handles all loop logic (everything to make the bot run)
// arguments : none
// returns : none
void loop() {
  wall.readPhotoTransistorValue();
  wall.checkWall();
  ls.readPhotoTransistorValue();
  ls.checkColor();
  ws.run();
  bool wallDetect = wall.getWallDetectedBool();
  //Serial.println(wallDetect);
  if (stateMachine = 0 and wallDetect) {
  //   client.beginMessage(TYPE_TEXT);
  //   client.print(state2);
  //   client.endMessage();  
  //   stateNum = 2;
  //   Serial.print("REVERSE: ");
  //   Serial.println(stateNum);
  //   state.buttonStateSetter(stateNum);
  //   stateNum = 4;
  //   state.buttonStateSetter(stateNum);
  //   state.buttonStateFunctions();
  //   delay(1000);
  // } else {
  //   stateNum = ws.getStateNumber();
  //   // Serial.print("Main Serial Num: ");
  //   // Serial.println(stateNum);
  //   state.buttonStateSetter(stateNum);
  }
  // state.buttonStateFunctions();
  bd.ReadVoltage();
  //delay(10);
}
