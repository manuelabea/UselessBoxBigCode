#ifndef SENSOR_h
#define SENSOR_h

#include "Arduino.h"

void setUpSensor();
void sensorInterrupt();
bool getSensorInterruptedState();
void sensorInterruptedMethod();

void lightUp();

#endif