// This is an example handler that can be run on the Feather Huzzah
#include <BakeryQuest.h>

BakeryQuest bq;
Spell spell;

// Constants for configuration
#define WIFI_SSID ""
#define WIFI_PASS ""
#define IFTTT_KEY ""
#define ON_ACTION ""
#define OFF_ACTION ""
#define DELAY 3000

bool activated = false;

void setup() {
  Serial.begin(115200);

  while (!Serial) { delay(50); }

  bq.connect(WIFI_SSID, WIFI_PASS, IFTTT_KEY);

  pinMode(LED_BUILTIN, OUTPUT);
  // Turn the LED off
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if (bq.spellCast(&spell)) {
    // Turn the LED on so we know a spell was performed
    digitalWrite(LED_BUILTIN, LOW);

    // Do something here

    // Intentional delay so that multiple shakes of the want don't collide
    delay(DELAY);

    // Turn the LED off so we know it's ready for another spell
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
