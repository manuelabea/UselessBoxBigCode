#ifndef ACTIONS_h
#define ACTIONS_h

#include "Arduino.h"
#include "myservo.h"
#include "myLidServo.h"

enum actionStates_t {
  NOACTION,
  ACTION1,
  ACTION2,
  ACTION3,
  FINISHEDACTION
};

void setActionState(actionStates_t _state);
actionStates_t getActionState();
void setFinishedPrevStep(bool _finishedPrevStep);
void checkActionState();
bool getfinishedPrevStep();

#endif