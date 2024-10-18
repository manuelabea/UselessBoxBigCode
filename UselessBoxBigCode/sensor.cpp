#include "led.h"
#include "sensor.h"

const int sensorPin = 12;
bool sensorInterrupted;
volatile int sensorState;
volatile int oldSensorState;

///////
const int frontSensorPin = 10;
bool frontsensorInterrupted;
volatile int frontsensorState;
volatile int oldfrontSensorState;

const int backSensorPin = 5;
bool backsensorInterrupted;
volatile int backsensorState;
volatile int oldbackSensorState;


bool edgeDetected;



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