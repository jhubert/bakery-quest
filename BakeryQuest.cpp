/*
  Test.h - Test library for Wiring - implementation
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// include this library's description file
#include <string>
#include <ir_Magiquest.h>
#include <IRrecv.h>
#include "BakeryQuest.h"

#include <ESP8266WiFi.h>

const uint16_t kRecvPin = 14;
IRrecv irrecv(kRecvPin);

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

void BakeryQuest::connect(std::string wifi_ssid, std::string wifi_pass, std::string ifttt_key) {
  Serial.print("Connecting...");

  WiFiClient wifiClient;

  WiFi.begin(wifi_ssid.c_str(), wifi_pass.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Start the IR receiver
  irrecv.enableIRIn();

  // wifiSSID = wifi_ssid;
  // wifiPASS = wifi_pass;
  iftttKey = ifttt_key;

  Serial.println(" Done");
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

std::pair<std::string, int> BakeryQuest::listenForWand() {
  decode_results results;
  std::string name = "Unknown";

  if (irrecv.decode(&results)) {
    if (results.decode_type == MAGIQUEST) {
      if (results.command > 2050) {
        Serial.print("wand_id: ");
        Serial.println(results.address);
        Serial.print("magnitude: ");
        Serial.println(results.command);
        Serial.println("");

        if (results.address == 26005324) { name = "Ben"; }
        if (results.address == 29378092) { name = "Zoe"; }

        irrecv.resume();
        return std::make_pair(name, results.command);
      } else {
        Serial.print("wand_id: ");
        Serial.println(results.address);
        Serial.print("Not strong enough: ");
        Serial.println(results.command);
      }
    } else {
      Serial.println("Unknown IR signal.");
      Serial.println(results.decode_type);
      Serial.println(results.address);
    }
  }

  irrecv.resume();  // Receive the next value
  return std::make_pair(name, 0);
}

boolean BakeryQuest::connectedToIFTTT() {
  Serial.println("Connecting to http://maker.ifttt.com on port 80.");

  int tcpResponse = wifiClient.connect("maker.ifttt.com", 80);

  return tcpResponse > 0;
}

void BakeryQuest::trigger(std::string action)
{
  if (connectedToIFTTT()) {
    std::string command = "GET /trigger/" + action + "/with/key/" + iftttKey + " HTTP/1.1\nHost: maker.ifttt.com\nConnection: close\n\n";

    Serial.println(command.c_str());
    // wifiClient.print(command.c_str());
  } else {
    Serial.println("Not connected");
  }
}
