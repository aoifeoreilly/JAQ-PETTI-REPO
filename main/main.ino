/*
  main.cpp - Library for main fuctionality code.
  Created by Quan Vu, October 8, 2024.
*/

#include "Arduino.h"
#include "WallDetection.h"
#include "StateMachine.h"
#include "LightSensing.h"
#include "ServerCommunication.h"

WallDetection wall;
StateMachine state;

void setup() {
  Serial.begin(9600);
  wall.begin();
  state.begin();
}

void loop() {
  wall.checkWall();
  state.loop();
}
