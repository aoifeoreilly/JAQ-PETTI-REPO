/*
  WebSocket.h - Library for Wall Detection code
  Created by Quan Vu, October 31, 2024.
*/

#ifndef WebSocket_h
#define WebSocket_h

#include "Arduino.h"
#include "StateMachine.h"
#include <ArduinoHttpClient.h>
#include <WiFi.h>

char ssid[] = "tufts_eecs";
char pass[] = "foundedin1883";

char serverAddress[] = "34.28.153.91";  // server address
int port = 80;

WiFiClient wifi;
WebSocketClient client = WebSocketClient(wifi, serverAddress, port);
String clientID = "8050D1451904"; //Insert your Server ID Here!
int status = WL_IDLE_STATUS;
int count = 0;

class WebSocket
{
  public:
    void begin();
    void run();
    void checkNumbers(String message);
    int getStateNumber();
    int getDelayNumber();
    void calculateDelay();
    int getDelayAmountNumber();
    bool getResetTwirl();
    void setResetTwirl(bool twirl);
    int getBotState();
    int getBotCommunication();
  

  private:
    String readMessage;
    int state = 0;
    int delayNum = 0;
    bool tenPlus = false;
    bool tenMinus = false;
    bool fiftyPlus = false;
    bool fiftyMinus = false;
    bool hundredPlus = false;
    bool hundredMinus = false;
    bool resetTwirl = false;

    int botCommunication = 0;
    int delayState = 0;
    int delayAmount = 1650;
    
    int botState = 0;
};

#endif
