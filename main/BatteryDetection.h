// /*
//   BatteryDetection.h - Library for Wall Detection code
//   Created by Quan Vu, October 31, 2024.
// */

// #ifndef BatteryDetection_h
// #define BatteryDetection_h

// #include "Arduino.h"


// class BatteryDetection
// {
//   public:
//     BatteryDetection();
//     void begin();
//     void initPins();
    
//   private:
// };

// #endif

/*
  BatteryDetection.h - Library for Wall Detection code
  Created by Quan Vu, October 31, 2024.
*/

#ifndef BatteryDetection_h
#define BatteryDetection_h

#include "Arduino.h"
#include "WebSocket.h"

const int v_divider_pin = A1; //could change


class BatteryDetection
{
  public:
    BatteryDetection();
    void begin();
    void ReadVoltage();
    
  private:
    int BatteryVoltage = 0;
    bool BatteryLowDetected = false;
};

#endif