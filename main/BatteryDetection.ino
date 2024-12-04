// /*
//   BatteryDetection.cpp - Library for Wall Detection code.
//   Created by Quan Vu, October 31, 2024.
// */

// #include "Arduino.h"
// #include "WallDetection.h"

// // name: BatteryDetection (constructor)
// // function : creates an instance of BatteryDetection and calls begin() function.
// // arguments : none
// // returns : none
// BatteryDetection::BatteryDetection() {
  
// }

// // name: begin
// // function : sets the pinMode of each pin and initializes the pins accordingly
// // arguments : none
// // returns : none
// void BatteryDetection::begin() {
// }

// // name: initPins
// // function : initializes the pins to aid in the BatteryDetection functionality
// // arguments : none
// // returns : none
// void BatteryDetection::initPins() {

// }

/*
  BatteryDetection.cpp - Library for Wall Detection code.
  Created by Quan Vu, October 31, 2024.
*/

#include "Arduino.h"
#include "BatteryDetection.h"
#include <ArduinoHttpClient.h>
#include <WiFi.h>

// name: BatteryDetection (constructor)
// function : creates an instance of BatteryDetection and calls begin() function.
// arguments : none
// returns : none
BatteryDetection::BatteryDetection() {
  begin();
}

// name: begin
// function : sets the pinMode of each pin and initializes the pins accordingly
// arguments : none
// returns : none
void BatteryDetection::begin() {
  pinMode(A4, INPUT); //A2 is just a sample pin, not sure which pins are taken
  // ReadVoltage();
}

// name: ReadVoltage
// function : Reads Voltage from voltage divider circuit
// arguments : none
// returns : none
void BatteryDetection::ReadVoltage() {
  String battery_message = "Battery is Low!";
  String b_msg = "Battery is High";
  int test = analogRead(A4);
  BatteryVoltage = (test * 5) / 1023;
  Serial.print("Testing Analog Read: ");
  Serial.println(test);
  Serial.print("BatteryVoltage: ");
  Serial.println(BatteryVoltage);
  if ((BatteryVoltage < 2.35) and client.connected()) {
    if (!BatteryLowDetected) {
      client.beginMessage(TYPE_TEXT);
      client.print(battery_message);
      client.endMessage();
      BatteryLowDetected = true;
    }
  // } else {
  //   client.beginMessage(TYPE_TEXT);
  //   client.print(b_msg);
  //   client.endMessage();
  }
}