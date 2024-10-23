#ifndef MOTOR_h
#define MOTOR_h

#include "Arduino.h"
#include <DRV8833.h>
#include "sensor.h"

enum motorStates_t {
  NOMOTORACTION,
  FINISHEDMOTORSTEP,
  DRIVE180,
  JUSTDRIVE,
  REVERSE_TIMED,
  FORWARD_TIMED
};

void setMotorState(motorStates_t _drivingState);
motorStates_t getMotorState();
void setUpMotor();
void driveMotor();
void stopMotor();
void attachMotor();
void detachMotor();
unsigned long getTimePassedSinceMotorStart();
void setTimePassedSinceMotorStart();
void checkMotorState();
bool getFinishedMotorStep();

#endif