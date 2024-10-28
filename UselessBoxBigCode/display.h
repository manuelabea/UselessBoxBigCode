#ifndef DISPLAY_h
#define DISPLAY_h

#include "Arduino.h"
#include "actions.h"

enum displayStates_t {
  NODISPLAYACTION,
  DISPLAYSHOWING_HOMERGIF
};

void setDisplayPicID(int _picID);
void playHomerGIF();
void checkDisplayState();
void setDisplayState(displayStates_t _state);
void setDisplayChangeTimestamp();

#endif