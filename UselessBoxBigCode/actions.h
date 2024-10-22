#ifndef ACTIONS_h
#define ACTIONS_h

#include "Arduino.h"
#include "myservo.h"
#include "myLidServo.h"
#include "sensor.h"
#include "motor.h"

enum actionStates_t {
  NOACTION,
  ACTION1,
  ACTION2,
  UNTOGGLED_ACTION1,
  UNTOGGLED_ACTION2
};

void setActionState(actionStates_t _state);
actionStates_t getActionState();
void setFinishedPrevStep(bool _finishedPrevStep);
void checkActionState();
bool getfinishedPrevStep();
//int getActionCounter();
//void setActionCounter(int _newActionCounter);

#endif