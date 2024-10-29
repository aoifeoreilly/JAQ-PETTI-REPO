/*
  WallDetection.h - Library for Wall Detection code
  Created by Quan Vu, October 8, 2024.
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
    void checkStateNum(String message);
    void getStateNumber();
  private:
    String readMessage;
    int state = 0;
};

#endif
