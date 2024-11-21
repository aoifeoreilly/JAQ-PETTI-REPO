#include "Arduino.h"
#include "WebSocket.h"

/*
  Simple WebSocket client for ArduinoHttpClient library
  Connects to the WebSocket server, and sends a hello
  message every 5 seconds

  created 28 Jun 2016
  by Sandeep Mistry
  modified 22 Jan 2019
  by Tom Igoe
  Modified by Gabriel Sessions
  for EE 31
  Modified by Quan Vu
  for EE 31 Project October 31, 2024

  this example is in the public domain
*/

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
/////// WiFi Settings ///////

void WebSocket::begin(){
  Serial.begin(9600);
    while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to Network named: ");
      Serial.println(ssid);                   // print the network name (SSID);

      // Connect to WPA/WPA2 network:
      status = WiFi.begin(ssid, pass);
    }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println("starting WebSocket client");
  client.begin();
  client.beginMessage(TYPE_TEXT);
  client.print(clientID);
  client.endMessage();
}

void WebSocket::run(){
  if (client.connected()) {
    // check if a message is available to be received
    int messageSize = client.parseMessage();
    if (messageSize > 0) {
      readMessage = client.readString();
      Serial.println("Received a message:");
      Serial.println(readMessage);
      checkStateNum(readMessage);
    }

    // wait 10ms
    delay(10);
  } else {
    Serial.println("disconnected");
  }
}

// name: checkStateNum
// function : checks the message for WebSocket, parses it to only see the end, and changes states depending on message conditionals
// arguments : a string with the message from WebSocket
// returns : none
void WebSocket::checkStateNum(String message){
  if(message.endsWith("State 1")){
    state = 1;
  } else if (message.endsWith("State 2")){
    state = 2;
  } else if (message.endsWith("State 3")){
    state = 3;
  } else if (message.endsWith("State 4")){
    state = 4;
  } else if (message.endsWith("State 5")){
    state = 5;
  } else if (message.endsWith("State 6")){
    state = 6;
  } else if (message.endsWith("State 0")){
    state = 0;
  }
}
// name: getStateNumber
// function : getter for StateNumber
// arguments : none
// returns : none
int WebSocket::getStateNumber(){
  return state;
}

