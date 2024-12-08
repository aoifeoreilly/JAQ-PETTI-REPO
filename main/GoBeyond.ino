/*
  GoBeyond.ino - 
  Created by Aoife O'Reilly, December 4, 2024.
*/
#include "Arduino.h"
#include "GoBeyond.h"

// name: GoBeyond (constructor)
// function : creates an instance of GoBeyond and calls begin() function.
// arguments : none
// returns : none
GoBeyond::GoBeyond(){
  begin();
}

// name: begin
// function : sets the pinMode of each pin to outpur
// arguments : none
// returns : none
void GoBeyond::begin(){
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  //initPins();
}

// name: initPins
// function : initializes the pins
// arguments : none
// returns : none
void GoBeyond::initPins(){
  // digitalWrite(leftLED, HIGH);
  // digitalWrite(rightLED, HIGH);
}

void GoBeyond::leftLightOnlyOn(){
  digitalWrite(leftLED, HIGH);
  digitalWrite(rightLED, LOW);
}

void GoBeyond::rightLightOnlyOn(){
  digitalWrite(rightLED, HIGH);
  digitalWrite(leftLED, LOW);
}

void GoBeyond::bothLightsOn(){
  digitalWrite(leftLED, HIGH);
  digitalWrite(rightLED, HIGH);
}

