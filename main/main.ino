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
#include "GoBeyond.h"

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
  int lightSensingColor = ls.getColor();
  ws.run();
  bool wallDetect = wall.getWallDetectedBool();
  stateNum = ws.getStateNumber();
  int color = ls.getColor();

  if (lightSensingColor == 1){
    Serial.println("BLACK");
  } else if (lightSensingColor == 2){
    Serial.println("BLUE");
  } else if (lightSensingColor == 3){
    Serial.println("RED");
  } else if (lightSensingColor == 4){
    Serial.println("YELLOW");
  } else if (lightSensingColor == 5){
    Serial.println("UNKNOWN :(");
  }

  //BLACK = 1
  //BLUE = 2
  //RED = 3
  //YELLOW = 4
  //UNKNOWN = 5
  // Serial.print("StateMachine: ");
  // Serial.println(stateMachine);
  // Serial.print("StateNum: ");
  // Serial.println(stateNum);

  if(stateNum == 8){
    stateNum = 0;
    state.buttonStateSetter(stateNum);
    stateMachine = 0;
    state.buttonStateFunctions();
  }

  if (stateMachine == 0 and stateNum == 7){
    stateNum = 1;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    stateMachine += 1;
  }
  // Serial.println(wallDetect);



  if (stateMachine == 1 and wallDetect) {
    // client.beginMessage(TYPE_TEXT);
    // client.print(state2);
    // client.endMessage();
    stateNum = 2;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    delay(400);

    stateNum = 4;
    // Serial.print("REVERSE: ");
    // Serial.println(stateNum);
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    delay(1000);

    stateNum = 1;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    // stateNum = 1; 
    // state.buttonStateSetter(stateNum);
    // state.buttonStateFunctions();
    stateMachine += 1;                     // State 0 is done, 
  }

  if(stateMachine == 2 and color == 3){
    stateNum = 0;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    // delay(500);
    // stateNum = 1; 
    // state.buttonStateSetter(stateNum);
    // state.buttonStateFunctions();
    // while (!wallDetected){
    //   Serial.println("KEEP GOING FORWARD!");
    // }
    // stateNum = 4;
    // state.buttonStateSetter(stateNum);
    // state.buttonStateFunctions();
    // delay(500);

    stateMachine += 1; //State 1 is done
  }

  // if
  // } else {
  //   // stateNum = ws.getStateNumber();
  //   // // Serial.print("Main Serial Num: ");
  //   // // Serial.println(stateNum);
  //   // state.buttonStateSetter(stateNum);
  // }
  //state.buttonStateFunctions();
  // bd.ReadVoltage();
}
