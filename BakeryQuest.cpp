/*
  BakeryQuest.cpp - A wrapper around the ESP8266 and IR libraries to
  use Feather Huzzah as a wand receiver
*/

#include "BakeryQuest.h"
#include <string>
#include <ir_Magiquest.h>
#include <IRrecv.h>
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

bool BakeryQuest::spellCast(Spell *spell) {
  decode_results results;

  spell->name = "";
  spell->magnitude = 0;

  if (irrecv.decode(&results)) {
    if (results.decode_type == MAGIQUEST) {
      // This 2050 number is somewhat arbitrary. I had a hard time getting
      // reliable magnitude readings from the different wands.
      if (results.command > 2050) {
        Serial.print("wand_id: ");
        Serial.println(results.address);
        Serial.print("magnitude: ");
        Serial.println(results.command);
        Serial.println("");

        // These are the wand ids for my kid's wands
        if (results.address == 26005324) { spell->name = "Ben"; }
        if (results.address == 29378092) { spell->name = "Zoe"; }

        spell->magnitude = results.command;
      } else {
        Serial.print("wand_id: ");
        Serial.println(results.address);
        Serial.print("Not strong enough: ");
        Serial.println(results.command);
      }
    }

    irrecv.resume();
  }

  if (spell->magnitude > 0) {
    return true;
  } else {
    return false;
  }
}

bool BakeryQuest::connectedToIFTTT() {
  Serial.println("Connecting to http://maker.ifttt.com on port 80.");

  int tcpResponse = wifiClient.connect("maker.ifttt.com", 80);

  return tcpResponse > 0;
}

void BakeryQuest::trigger(std::string action)
{
  if (connectedToIFTTT()) {
    std::string command = "GET /trigger/" + action + "/with/key/" + iftttKey + " HTTP/1.1\nHost: maker.ifttt.com\nConnection: close\n\n";

    Serial.println(command.c_str());
    wifiClient.print(command.c_str());
  } else {
    Serial.println("Not connected");
  }
}
