/*
  BakeryQuest.h - A wrapper around the ESP8266 and IR libraries to
  use Feather Huzzah as a wand receiver
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

class BakeryQuest
{
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

