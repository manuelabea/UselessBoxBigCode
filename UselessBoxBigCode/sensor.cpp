

#include "led.h"

const int sensorPin = 12;

bool sensorInterrupted;
volatile int sensorState;
volatile int oldSensorState;

void setUpSensor(){
  pinMode(sensorPin, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(sensorPin), sensorInterrupt, CHANGE);
}

void sensorInterrupt(){
  sensorInterrupted = true;
}

bool getSensorInterruptedState(){
  return sensorInterrupted;
}

void sensorInterruptedMethod(){
  sensorInterrupted == false;
  sensorState = digitalRead(sensorPin);
  if (sensorState != oldSensorState) {
    oldSensorState = sensorState;
    lightUp();
  }
}

void lightUp(){
  if (sensorState == HIGH) { //
    setLEDState(NOLED);
  }
  if (sensorState == LOW) { //
    setLEDState(GREEN);
  }
}