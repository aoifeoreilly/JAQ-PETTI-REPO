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
GoBeyond gb;

volatile int stateMachine = 0;
int stateNum = 0;
int previousStateNum = 0;
int delayState = 0;
int delayNumber = 0;
int botStateMain = 0;
int firstColor = 0;
int turnNumber = 0;
bool delayBool = false;
int SoloOrTeamStateNum = 0;
bool teamDemo = false;
int teamDemoBotNum = 0;
int botCommunication = 0;

bool firstWallDetect = false;
bool secondWallDetect = false;
bool thirdWallDetect = false;
bool fourthWallDetect = false;

bool goBeyond = false;

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
  gb.begin();
}

// name: loop
// function : main function that handles all loop logic (everything to make the bot run)
// arguments : none
// returns : none
void loop() {

  ws.run();
  stateNum = ws.getStateNumber();
  delayState = ws.getDelayNumber();
  delayNumber = ws.getDelayAmountNumber();
  delayBool = ws.getResetTwirl();
  botStateMain = ws.getBotState();
  botCommunication = ws.getBotCommunication();

  if (botStateMain == 1) {  //BOT 1 SOLO TEST
    firstColor = 3;         //RED
    turnNumber = 3;         //COUNTERCLOCKWISE
    teamDemo = false;
  } else if (botStateMain == 2) {  //BOT 2 SOLO TEST
    firstColor = 2;                //BLUE
    turnNumber = 4;                //CLOCKWISE
    teamDemo = false;
  } else if (botStateMain == 3) {  //BOT 1 TEAM TEST
    firstColor = 3;  //RED
    turnNumber = 3;  //COUNTERCLOCKWISE
    teamDemo = true;
  } else if (botStateMain == 4) {  // BOT 2 TEAM TEST
    firstColor = 2; //BLUE
    turnNumber = 4; //CLOCKWISE
    teamDemo = true;
  }

  // TWIRL STATE (180 DEGREE TURN) - USED TO CALIBRATE A PERFECT 180 TURN BEFORE STARTING ON THE COURSE
  if (delayState == 7 and !delayBool) {
    stateNum = turnNumber;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    delay(delayNumber);
    ws.setResetTwirl(true);
    stateNum = 0;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
  }

  // RESET STATE - USED TO RESET EVERYTHING BACK TO INITIAL CONDITIONS
  if (stateNum == 8) {
    stateNum = 0;
    stateMachine = 1;
    botCommunication = 0;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    wall.setWallNum(1);
  }

  wall.readPhotoTransistorValue();
  wall.checkWall();
  ls.readPhotoTransistorValue();
  ls.checkColor();
  int lightSensingColor = ls.getColor();
  bool wallDetect = wall.getWallDetectedBool();

  // CALIBRATION STATE - USED TO CALIBRATE THE COLOR SENSING EVERY TEST RUN
  if (stateMachine == 0 and stateNum == 100) {
    ls.calibrate();
    stateNum = 0;
    state.buttonStateSetter(stateNum);
    state.buttonStateFunctions();
    stateMachine += 1;
  }

  if (teamDemo == false){
    // STATEMACHINE 1 - STARTS GOING FORWARD AT THE BEGINNING
    if (stateMachine == 1 and stateNum == 7) {
      stateNum = 1;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      stateMachine += 1;
    }

    // STATEMACHINE 2 - WHEN A WALL IS DETECTED, THE BOT STOPS, TURNS 180 DEGREES, THEN CONTINUES FORWARD
    if (stateMachine == 2 and wallDetect) {

      gb.bothLightsOn();
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);
      gb.bothLightsOff();

      stateNum = 2;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      gb.bothLightsOn();
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);
      gb.bothLightsOff();

      gb.turnDirection(turnNumber);
      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber);

      gb.bothLightsOn();
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);
      gb.bothLightsOff();

      stateNum = 1;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      stateMachine += 1;

    }

    // STATEMACHINE 3 - IF THE FIRST COLOR IS DETECTED, THEN STOP AND TURN 90 DEGREES TO GET ON THE LANE
    if (stateMachine == 3 and lightSensingColor == firstColor) {

      gb.bothLightsOn();
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);
      gb.bothLightsOff();

      gb.turnDirection(turnNumber);
      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 2);
      gb.bothLightsOff();

      stateNum = 1;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateMachine += 1;
    }

    // STATEMACHINE 4 - STATE FOLLOWS THE LANE OF THE FIRST COLOR UNTIL THE WALL IS DETECTED. IF WALL IS DETECTED, STOP AND GO TO THE NEXT STATE
    if (stateMachine == 4) {
      int lsColor = ls.getColor();
      int stateLS = ls.laneFollowing(lsColor, firstColor);
      if (!wallDetect) {
        state.buttonStateSetter(stateLS);
        state.buttonStateFunctions();
      } else {
        gb.bothLightsOn();
        stateNum = 0;
        state.buttonStateSetter(stateNum);
        state.buttonStateFunctions();
        delay(delayNumber / 4);
        gb.bothLightsOff();
        stateMachine += 1;
      }
    }

    // STATEMACHINE 5 - TURN 90 DEGREES TO FACE THE MIDDLE LANE. ONCE TURN IS COMPLETED, MOVE FORWARD AND GO TO THE NEXT STATE
    if (stateMachine == 5) {
      gb.turnDirection(turnNumber);
      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 2);
      gb.bothLightsOff();

      gb.bothLightsOn();
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);
      gb.bothLightsOff();

      stateNum = 1;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      stateMachine += 1;
    }

    // STATEMACHINE 6 - IF THE YELLOW IS DETECTED, THEN STOP AND TURN 90 DEGREES TO GET ON THE YELLOW LANE
    if (stateMachine == 6 and lightSensingColor == 4) {
      gb.bothLightsOn();
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);
      gb.bothLightsOff();

      gb.turnDirection(turnNumber);
      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 2);
      gb.bothLightsOff();

      stateNum = 1;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      stateMachine += 1;
    }

    // STATEMACHINE 7 - STATE FOLLOWS THE YELLOW LANE UNTIL THE WALL IS DETECTED. IF WALL IS DETECTED, STOP AND GO TO THE NEXT STATE
    if (stateMachine == 7) {
      int lsColor = ls.getColor();
      int stateLS = ls.laneFollowing(lsColor, firstColor);
      if (!wallDetect) {
        state.buttonStateSetter(stateLS);
        state.buttonStateFunctions();
      } else {
        gb.bothLightsOn();
        stateNum = 0;
        state.buttonStateSetter(stateNum);
        state.buttonStateFunctions();
        delay(delayNumber / 4);
        stateMachine += 1;
        gb.bothLightsOff();
      }
    }

    // STATEMACHINE = 8 - TURN 90 DEGREES TO FACE THE FINAL WALL. ONCE TURN IS COMPLETED, MOVE FORWARD AND GO TO THE NEXT STATE
    if (stateMachine == 8) {
      gb.turnDirection(turnNumber);
      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 2);
      gb.bothLightsOff();

      gb.bothLightsOn();
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);
      gb.bothLightsOff();

      stateNum = 1;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay((delayNumber / 2) + (delayNumber / 5));

      stateMachine += 1;
    }

    // STATEMACHINE = 9 - GOES FORWARD UNTIL IS DETECTS THE WALL. THEN TURNS 180 AND REVERSES INTO START STATE.
    if (stateMachine == 9 and wallDetect) {
      gb.bothLightsOn();
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);
      gb.bothLightsOff();

      gb.turnDirection(turnNumber);
      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber);
      gb.bothLightsOff();

      gb.bothLightsOn();
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      stateMachine += 1;
      gb.bothLightsOff();

      stateNum = 2;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 2);

      gb.bothLightsOn();
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);
      gb.bothLightsOff();

      stateMachine += 1;
    }
  }























if (botStateMain == 3){ // IF IT IS TEAM TRIALS AS BOT A
    // STATEMACHINE 1 - STARTS GOING FORWARD AT THE BEGINNING
    if (stateMachine == 1 and botCommunication == 5) {
      client.beginMessage(TYPE_TEXT);
      client.print("JAQPETTI STARTING! CHOO CHOO!");
      client.endMessage();

      stateNum = 1;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      stateMachine += 1;
    }

    // STATEMACHINE 2 - WHEN A WALL IS DETECTED, THE BOT STOPS, TURNS 180 DEGREES, THEN CONTINUES FORWARD
    if (stateMachine == 2 and wallDetect) {
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      // client.beginMessage(TYPE_TEXT);
      // client.print(state2);
      // client.endMessage();
      stateNum = 2;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber);

      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateNum = 1;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      stateMachine += 1;

    }

    // STATEMACHINE 3 - IF THE FIRST COLOR IS DETECTED, THEN STOP AND TURN 90 DEGREES TO GET ON THE LANE
    if (stateMachine == 3 and lightSensingColor == firstColor) {

      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay((delayNumber * 5) / 8);

      client.beginMessage(TYPE_TEXT);
      client.print("JAQPETTI FOUND RED");
      client.endMessage();

      stateMachine += 1;
    }

    // STATEMACHINE 4 - STATE FOLLOWS THE LANE OF THE FIRST COLOR UNTIL THE WALL IS DETECTED. IF WALL IS DETECTED, STOP AND GO TO THE NEXT STATE
    if (stateMachine == 4) {
      int lsColor = ls.getColor();
      int stateLS = ls.laneFollowing(lsColor, firstColor);
      if (!wallDetect) {
        state.buttonStateSetter(stateLS);
        state.buttonStateFunctions();
      } else {
        stateNum = 0;
        state.buttonStateSetter(stateNum);
        state.buttonStateFunctions();
        delay(delayNumber / 4);
        stateMachine += 1;
      }
    }

    // STATEMACHINE 5 - TURN 90 DEGREES TO FACE THE MIDDLE LANE. ONCE TURN IS COMPLETED, MOVE FORWARD AND GO TO THE NEXT STATE
    if (stateMachine == 5) {
      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 2);

      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateNum = 1;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      stateMachine += 1;
    }

    // STATEMACHINE 6 - IF THE YELLOW IS DETECTED, THEN STOP AND TURN 90 DEGREES TO GET ON THE YELLOW LANE
    if (stateMachine == 6 and lightSensingColor == 4) {
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay((delayNumber * 2) / 3);

      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateMachine += 1;
    }

    if (stateMachine == 7 and botCommunication == 1){
      delay(1000);
      stateMachine += 1;
    }

    // STATEMACHINE 7 - STATE FOLLOWS THE YELLOW LANE UNTIL THE WALL IS DETECTED. IF WALL IS DETECTED, STOP AND GO TO THE NEXT STATE
    if (stateMachine == 8) {
      int lsColor = ls.getColor();
      int stateLS = ls.laneFollowing(lsColor, firstColor);
      if (!wallDetect) {
        state.buttonStateSetter(stateLS);
        state.buttonStateFunctions();
        //delay(delayNumber / 3);
      } else {
        stateNum = 0;
        state.buttonStateSetter(stateNum);
        state.buttonStateFunctions();
        delay(delayNumber / 4);
        stateMachine += 1;
      }
    }

    // STATEMACHINE = 8 - TURN 90 DEGREES TO FACE THE FINAL WALL. ONCE TURN IS COMPLETED, MOVE FORWARD AND GO TO THE NEXT STATE
    if (stateMachine == 9) {
      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay((delayNumber * 5) / 8);

      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateNum = 1;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay((delayNumber / 2) + (delayNumber / 5));

      stateMachine += 1;
    }

    // STATEMACHINE = 9 - GOES FORWARD UNTIL IS DETECTS THE WALL. THEN TURNS 180 AND REVERSES INTO START STATE.
    if (stateMachine == 10 and wallDetect) {
      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber + 350);

      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();

      stateNum = 2;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 3);

      stateNum = 0;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateMachine += 1;
    }

    if (stateMachine == 11){
      delay(3000);
      client.beginMessage(TYPE_TEXT);
      client.print("JAQPETTI RETURNED HOME");
      client.endMessage();
    }
  }
  







































// BOT 2 TEAM DEMO
if (botStateMain == 4){
    // Serial.print("stateMachine In Loop: ");
    // Serial.println(stateMachine);
    
    // STATEMACHINE 1 - STARTS GOING FORWARD AT THE BEGINNING
    if (stateMachine == 1 and botCommunication == 2) {
      delay(12000);

      client.beginMessage(TYPE_TEXT);
      client.print("JAQPETTI STARTING! CHOO CHOO!");
      client.endMessage();

      state.buttonStateSetter(1);
      state.buttonStateFunctions();
      stateMachine += 1;
    }

    // STATEMACHINE 2 - WHEN A WALL IS DETECTED, THE BOT STOPS, TURNS 180 DEGREES, THEN CONTINUES FORWARD
    if (stateMachine == 2 and wallDetect) {
      state.buttonStateSetter(0);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      state.buttonStateSetter(2);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      state.buttonStateSetter(0);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber);

      state.buttonStateSetter(0);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      state.buttonStateSetter(1);
      state.buttonStateFunctions();
      stateMachine += 1;

    }

    // STATEMACHINE 3 - IF THE FIRST COLOR IS DETECTED, THEN STOP AND TURN 90 DEGREES TO GET ON THE LANE
    if (stateMachine == 3 and lightSensingColor == firstColor) {

      state.buttonStateSetter(0);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 3);

      state.buttonStateSetter(0);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      client.beginMessage(TYPE_TEXT);
      client.print("JAQPETTI DETECTED BLUE LANE");
      client.endMessage();

      stateMachine += 1;
    }

    // STATEMACHINE 4 - STATE FOLLOWS THE LANE OF THE FIRST COLOR UNTIL THE WALL IS DETECTED. IF WALL IS DETECTED, STOP AND GO TO THE NEXT STATE
    if (stateMachine == 4 and botCommunication == 4) {
      delay(8000);
      stateMachine += 1;
    }

    if (stateMachine == 5) {
      int lsColor = ls.getColor();
      int stateLS = ls.laneFollowing(lsColor, firstColor);
      if (!wallDetect) {
        state.buttonStateSetter(stateLS);
        state.buttonStateFunctions();
      } else {
        state.buttonStateSetter(0);
        state.buttonStateFunctions();
        delay(delayNumber / 4);
        stateMachine += 1;
      }
    }

    // STATEMACHINE 5 - TURN 90 DEGREES TO FACE THE MIDDLE LANE. ONCE TURN IS COMPLETED, MOVE FORWARD AND GO TO THE NEXT STATE
    if (stateMachine == 6) {
      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber / 2);

      state.buttonStateSetter(0);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      state.buttonStateSetter(1);
      state.buttonStateFunctions();
      stateMachine += 1;
    }

    // STATEMACHINE 6 - IF THE YELLOW IS DETECTED, THEN STOP AND TURN 90 DEGREES TO GET ON THE YELLOW LANE
    if (stateMachine == 7 and lightSensingColor == 4) {
      state.buttonStateSetter(0);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay((delayNumber / 2) + (delayNumber / 5));

      state.buttonStateSetter(0);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateMachine += 1;
    }

    if (stateMachine == 8 and botCommunication == 3){
      state.buttonStateSetter(1);
      state.buttonStateFunctions();
      stateMachine += 1;
    }

    // STATEMACHINE 7 - STATE FOLLOWS THE YELLOW LANE UNTIL THE WALL IS DETECTED. IF WALL IS DETECTED, STOP AND GO TO THE NEXT STATE
    if (stateMachine == 9) {
      int lsColor = ls.getColor();
      int stateLS = ls.laneFollowing(lsColor, firstColor);
      if (!wallDetect) {
        state.buttonStateSetter(stateLS);
        state.buttonStateFunctions();
        //delay(delayNumber / 3);
      } else {
        stateNum = 0;
        state.buttonStateSetter(stateNum);
        state.buttonStateFunctions();
        delay(delayNumber / 4);
        stateMachine += 1;
      }
    }

    // STATEMACHINE = 8 - TURN 90 DEGREES TO FACE THE FINAL WALL. ONCE TURN IS COMPLETED, MOVE FORWARD AND GO TO THE NEXT STATE
    if (stateMachine == 10) {
      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay((delayNumber / 2) + (delayNumber / 5));

      state.buttonStateSetter(0);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      state.buttonStateSetter(1);
      state.buttonStateFunctions();
      delay((delayNumber / 2) + (delayNumber / 5));

      stateMachine += 1;
    }

    // STATEMACHINE = 9 - GOES FORWARD UNTIL IS DETECTS THE WALL. THEN TURNS 180 AND REVERSES INTO START STATE.
    if (stateMachine == 11 and wallDetect) {
      state.buttonStateSetter(0);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      stateNum = turnNumber;
      state.buttonStateSetter(stateNum);
      state.buttonStateFunctions();
      delay(delayNumber);

      state.buttonStateSetter(0);
      state.buttonStateFunctions();

      state.buttonStateSetter(2);
      state.buttonStateFunctions();
      delay(delayNumber / 3);

      state.buttonStateSetter(0);
      state.buttonStateFunctions();
      delay(delayNumber / 4);

      client.beginMessage(TYPE_TEXT);
      client.print("JAQPETTI RETURNED HOME!");
      client.endMessage();

      stateMachine += 1;
      delay(1000);
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
