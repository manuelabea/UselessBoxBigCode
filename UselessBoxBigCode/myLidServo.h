#ifndef MYLIDSERVO_h
#define MYLIDSERVO_h

#include "Arduino.h"
#include <Servo.h>
#include "toggle.h"
#include "display.h"
#include "myservo.h"

enum lidStates_t {
  INACTIVELID,
  FINISHEDSTEP,
  MOVINGLID,
  OPENLID,
  CLOSELID,
  RATTLELID,
  RATTLELID_OPEN,
  RATTLELID_CLOSE
};

void setUpLid();
void setLidState(lidStates_t _state);
lidStates_t getLidState();
void checkLidState();
void movementLid();
void setTargetPositionLid(int _updateIntervalLid, int _incrementLid, int _endPosLid);


#endif