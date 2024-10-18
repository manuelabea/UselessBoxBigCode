#include "led.h"
#include "sensor.h"

const int sensorPin = 12;
bool sensorInterrupted;
volatile int sensorState;
volatile int oldSensorState;

bool useSensor;

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

int interruptedByUser;


void setUpSensor() {
  pinMode(sensorPin, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(sensorPin), sensorInterrupt, CHANGE);
}

int getInterruptedByUser() {
  return interruptedByUser;
}

void setInterruptedByUser(int _newValue) {
  interruptedByUser = _newValue;
}

void attachSensor() {
  useSensor = true;
}

void detachSensor() {
  setInterruptedByUser(0);
  useSensor = false;
  detachMotor();
}

void sensorInterrupt() {
  sensorInterrupted = true;
}


bool getSensorInterruptedState() {
  return sensorInterrupted;
}

void sensorInterruptedMethod() {
  if (useSensor == true) {
    if (sensorInterrupted) {
      sensorInterrupted == false;
      sensorState = digitalRead(sensorPin);
      
      if (sensorState != oldSensorState) {
        oldSensorState = sensorState;
        if (sensorState == HIGH) {  //
          setLEDState(NOLED);
          if(getMotorState() == DRIVE180){
            
          } else {
            stopMotor();
          }
        }
        if (sensorState == LOW) {  //
          setLEDState(GREEN);
          setTimePassedSinceMotorStart();
          if (getActionState() == UNTOGGLED_ACTION2) {
            setMotorState(DRIVE180);
          } else if (getActionState() == UNTOGGLED_ACTION1) {
            setMotorState(JUSTDRIVE);
          }
          interruptedByUser++;
        }
      }
    }
  }
}
