#ifndef SENSOR_h
#define SENSOR_h

#include "Arduino.h"
#include "motor.h"
#include "actions.h"

void setUpSensor();
void sensorInterrupt();
bool getSensorInterruptedState();
void sensorInterruptedMethod();
void attachSensor();
void detachSensor();
int getInterruptedByUser();
void setInterruptedByUser(int _newValue);



#endif