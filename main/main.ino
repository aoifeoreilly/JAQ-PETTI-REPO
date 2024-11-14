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

WallDetection wall;
StateMachine state;
LightSensing ls;
WebSocket ws;

void setup() {
  Serial.begin(9600);
  wall.begin();
  state.begin();
  ls.begin();
  ws.begin();
}

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
  // state.test();
  delay(1000);
}
