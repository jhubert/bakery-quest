/*
  Test.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef BakeryQuest_h
#define BakeryQuest_h
#include <string>
#include <IRrecv.h>
#include <ESP8266WiFi.h>

struct Spell {
  std::string name;
  int magnitude;
};

// library interface description
class BakeryQuest
{
  // user-accessible "public" interface
  public:
    void connect(const std::string, const std::string, const std::string);
    void trigger(std::string);
    bool spellCast(Spell *spell);
    void resume();

  private:
    WiFiClient wifiClient;
    std::string iftttKey;
    bool connectedToIFTTT();
};

#endif

