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

volatile int delayTester = 0;
volatile int delayAmount = 0;
const int delay_180 = 50;
const int delay_90 = 25;



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

  ws.run();
  stateNum = ws.getStateNumber();
  delayTester = ws.getDelayNumber();
  if(stateNum == 8){
    stateNum = 0;
    stateMachine = 1;
    delayTester = 0;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
  }

  // if(stateMachine == 1 and stateNum == 1){
  //   stateNum = 1;
  //   state.buttonStateSetter(stateNum);
  //   state.buttonStateFunctions();
  //   stateMachine += 1;
  // }

  // if(stateMachine == 2 and stateNum == 2){
  //   stateNum = 2;
  //   state.buttonStateSetter(stateNum);
  //   state.buttonStateFunctions();
  //   stateMachine += 1;
  // }

  //   if(stateMachine == 3 and stateNum == 3){
  //   stateNum = 3;
  //   state.buttonStateSetter(stateNum);
  //   state.buttonStateFunctions();
  //   stateMachine += 1;
  // }

  // if(stateMachine == 4 and stateNum == 4){
  //   stateNum = 4;
  //   state.buttonStateSetter(stateNum);
  //   state.buttonStateFunctions();
  //   stateMachine += 1;
  // }

  // if(stateMachine == 5 and stateNum == 5){
  //   stateNum = 5;
  //   state.buttonStateSetter(stateNum);
  //   state.buttonStateFunctions();
  //   stateMachine += 1;
  // }

  // if(stateMachine == 6 and stateNum == 6){
  //   stateNum = 6;
  //   state.buttonStateSetter(stateNum);
  //   state.buttonStateFunctions();
  //   stateMachine += 1;
  // }


  wall.readPhotoTransistorValue();
  wall.checkWall();
  ls.readPhotoTransistorValue();
  ls.checkColor();
  int lightSensingColor = ls.getColor();
  bool wallDetect = wall.getWallDetectedBool();
  // int color = ls.getColor();
  // Serial.print("Color Num: ");
  // Serial.println(lightSensingColor);

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

  // if (stateMachine == 0 and stateNum == 7){
  //   stateNum = 1;
  //   state.buttonStateSetter(stateNum);
  //   state.buttonStateFunctions();
  //   stateMachine += 1;
  // }

  if(stateNum == 8){
    stateNum == 0;
    stateMachine == 1;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
  }

  if(stateMachine == 0 and stateNum == 100){
    ls.calibrate();
    stateNum = 0;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    stateMachine += 1;
  }
  // Serial.println(wallDetect);
  if(stateMachine == 1 and stateNum == 7){
    stateNum = 1;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    stateMachine += 1;
  }



  if (stateMachine == 2 and wallDetect) {
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
    delay(1600);

    stateNum = 1;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    // stateNum = 1; 
    // state.buttonStateSetter(stateNum);
    // state.buttonStateFunctions();
    stateMachine += 1;                     // State 0 is done, 
  }

  if(stateMachine == 3 and lightSensingColor == 3){
    stateNum = 3;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    delay(850);
    stateNum = 1;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    delay(1000);


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

  if(stateMachine == 4){
    int lsColor = ls.getColor();
    int stateLS = ls.laneFollowing(lsColor);
    if(!wallDetect){
      state.buttonStateSetter(stateLS);
      state.buttonStateFunctions();
      delay(250);
    } else {
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      stateMachine += 1;
      ls.setLeftRight(false);
    }
  }

    if(stateMachine == 5){
      stateNum = 3;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(1100);
      stateNum = 1;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();

      stateMachine += 1;
    }

    if(stateMachine == 6 and lightSensingColor == 4){
      stateNum = 3;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(600);
      stateNum = 1;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      stateMachine += 1;
    }

  if(stateMachine == 7){
    int lsColor = ls.getColor();
    int stateLS = ls.laneFollowing(lsColor);
    if(!wallDetect){
      state.buttonStateSetter(stateLS);
      state.buttonStateFunctions();
      delay(250);
    } else {
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      stateMachine += 1;
      ls.setLeftRight(false);
    }
  }

  if(stateMachine == 8){
    stateNum = 3;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    delay(1100);
    stateNum = 1;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    delay(1700);

    stateMachine += 1;
  }

  if (stateMachine == 9) {
    if(wallDetect){
      stateNum = 4;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(1700);
      stateNum = 0;    
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();   
      stateMachine += 1;   
    }       
  }














  // Serial.print("stateNum: ");
  // Serial.println(stateNum);
  // Serial.print("stateMachine: ");
  // Serial.println(stateMachine);

  // if
  // } else {
  //   // stateNum = ws.getStateNumber();
  //   // // Serial.print("Main Serial Num: ");
  //   // // Serial.println(stateNum);
  //   // state.buttonStateSetter(stateNum);
  // }
  // state.buttonStateFunctions();
  // bd.ReadVoltage();
}

