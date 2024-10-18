#ifndef MOTOR_h
#define MOTOR_h

#include "Arduino.h"
#include <DRV8833.h>
#include "sensor.h"


void setUpMotor();
void driveMotor();
void stopMotor();
void attachMotor();
void detachMotor();


#endif