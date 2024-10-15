#ifndef LED_h
#define LED_h

#include "Arduino.h"
#include "FastLED.h"

enum ledStates_t {
  NOLED,
  RED,
  GREEN,
  BLUE
};

void checkLEDState();
void setUpLED();
void setLEDState(ledStates_t _ledState);

#endif