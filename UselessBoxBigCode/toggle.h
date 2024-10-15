#ifndef TOGGLE_h
#define TOGGLE_h

#include "Arduino.h"

enum states_t {
  TOGGLED,
  UNTOGGLED,
  WAITING
};

void setToggleState(states_t _state);
states_t getToggleState();

#endif