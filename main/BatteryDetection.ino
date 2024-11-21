/*
  BatteryDetection.cpp - Library for Wall Detection code.
  Created by Quan Vu, October 31, 2024.
*/

#include "Arduino.h"
#include "BatteryDetection.h"

// name: BatteryDetection (constructor)
// function : creates an instance of BatteryDetection and calls begin() function.
// arguments : none
// returns : none
BatteryDetection::BatteryDetection() {
  
}

// name: begin
// function : sets the pinMode of each pin and initializes the pins accordingly
// arguments : none
// returns : none
void BatteryDetection::begin() {
  pinMode(A2, INPUT) //A2 is just a sample pin, not sure which pins are taken
  ReadVoltage();
}

// name: ReadVoltage
// function : Reads Voltage from voltage divider circuit
// arguments : none
// returns : none
void BatteryDetection::ReadVoltage() {
  string battery_message = "Battery is Low!";
  BatteryVoltage = (analogRead(A2))*(5/1023);
  if ((BatteryVoltage < 2.35) and client.connected) {
    client.beginMessage(TYPE_TEXT);
    client.print(battery_message);
    client.endMessage();
  }
}
