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
  // bd.begin();
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
  int stateNum = ws.getStateNumber();
  Serial.print("Main Serial Num: ");
  Serial.println(stateNum);
  state.buttonStateFunctions(stateNum);
  delay(1000);
}
