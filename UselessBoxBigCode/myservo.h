#ifndef MYSERVO_h
#define MYSERVO_h

#include "Arduino.h"
#include <Servo.h>
#include "toggle.h"
#include "actions.h"

enum servoStates_t {
  INACTIVE,
  MOVINGSERVO,
  FLIPSWITCHBACK, 
  FLIPSWITCHBACK2,
  RETURN,
  THREESTEPMOVEMENT1,
  THREESTEPMOVEMENT2,
  THREESTEPMOVEMENT3,
  FLIPSWITCHBACKSLOW
  
};

void setUpToggleArm();
void setServoState(servoStates_t _state);
servoStates_t getServoState();
void setNextServoState(servoStates_t _nextState);
void movement();
void setTargetPositionServo(int _updateInterval, int _increment, int _endPos);

#endif