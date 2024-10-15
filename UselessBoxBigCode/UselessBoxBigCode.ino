#include <Arduino.h>
#include <Bounce2.h>
#include <Servo.h>
//#include "FastLED.h"
#include <DRV8833.h>

#include "led.h"
#include "toggle.h"
#include "myservo.h"
#include "actions.h"
#include "myLidServo.h"
#include "display.h"

/*TOGGLE************************************************************************/
Bounce bounceToggle = Bounce();
bool toggled;
const int togglePin = 36;


/*Sensor************************************************************************/
const int sensorPin = 12;

bool sensorInterrupted;
volatile int sensorState;
volatile int oldSensorState;


/*Motor************************************************************************/
// Create an instance of the DRV8833:
//DRV8833 driver = DRV8833();

// Pin numbers
const int inputA1 = 14, inputA2 = 15, inputB1 = 19, inputB2 = 18;
const int nsleep = 22;
volatile int speed;


/*OTHER************************************************************************/
int actionCounter = 0;
unsigned long currentMillis;

/****************************************************************************************************/
/****************************************************************************************************/

void setup() {
  Serial.begin(115200); //Ist der USB
  Serial1.begin(9600); //Display
  actionCounter = 0;
    
  bounceToggle.attach(togglePin, INPUT_PULLUP);
  bounceToggle.interval(5);

  setToggleState(WAITING);
  setServoState(INACTIVE);

  attachInterrupt(digitalPinToInterrupt(togglePin), toggleToggled, CHANGE);

  pinMode(sensorPin, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(sensorPin), sensorInterrupt, CHANGE);

  setUpLED();

  setUpToggleArm();
  setUpLid();
  

  if(bounceToggle.read() == HIGH){
    setServoState(FLIPSWITCHBACK);
  }
  /*
  pinMode(nsleep, INPUT_PULLUP);
  digitalWrite(nsleep,HIGH); //enable Driver

  driver.attachMotorA(inputA1, inputA2);
  driver.attachMotorB(inputB1, inputB2);
  speed = 80;
*/
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  
  if (toggled == true) {
    debouncerMethod();
  }
  if (sensorInterrupted == true) {
    sensorInterruptedMethod();
  }
  switchStates();
  checkActionState();
  checkServoState();
  checkLidState();
  checkLEDState();

  /*Serial.print("lidState: ");
  Serial.print(lidState);
  Serial.print(" - ServoState: ");
  Serial.println(servoState);
*/
}

void toggleToggled(){
  toggled = true;
}

void sensorInterrupt(){
  sensorInterrupted = true;
}

void debouncerMethod(){
  bounceToggle.update();

  if ( bounceToggle.changed() ) {
    // THE STATE OF THE INPUT CHANGED
    // GET THE STATE
    int deboucedInput = bounceToggle.read();
    //Serial.println(deboucedInput);
    // IF THE CHANGED VALUE IS HIGH
    if ( deboucedInput == HIGH ) {
      setToggleState(TOGGLED);
      //Serial.print("actionCounter:"); Serial.println (actionCounter);
    } else {
      setToggleState(UNTOGGLED);
    }
  }
}

void sensorInterruptedMethod(){
  sensorInterrupted == false;
  sensorState = digitalRead(sensorPin);
  if (sensorState != oldSensorState) {
    oldSensorState = sensorState;
    lightUp();
  }
}

void switchStates(){
  switch (getToggleState()){
    case UNTOGGLED:
      Serial.print("nothing here");
      Serial.println(actionCounter);
      setServoState(RETURN);
      setLidState(CLOSELID);
      setToggleState(WAITING);
      setLEDState(BLUE);

      break;

    case TOGGLED:
      actionCounter++;
      Serial.print("actionCounter: "); Serial.println(actionCounter);
      setLidState(OPENLID);
      setLEDState(RED);
      /*if (actionCounter%3==1){
        //Serial.println("Got Here");
        actionState = ACTION1;
      } else if (actionCounter%3==2){
        //Serial.println("Got Here");
        actionState = ACTION2;
      } else {
        actionState = ACTION3;
        //Serial.println("Got Here");
      }*/
      setActionState(ACTION1);
      setToggleState(WAITING);
      break;

    case WAITING:
      break;
  }

}



void checkServoState(){
  
  switch (getServoState()) {
    case INACTIVE:
      break;
    case MOVINGSERVO:
      movement();
      break;
    case FLIPSWITCHBACK:
      setTargetPositionServo(10, 1, 170);
      setTargetPositionServo(10, 1, 85);
      setDisplayPicID(36);
      setNextServoState(INACTIVE);
      break;
    case RETURN:
      setTargetPositionServo(10, 1, 170);
      setDisplayPicID(33);
      break;
    case THREESTEPMOVEMENT1:
      setTargetPositionServo(10, 1, 130);
      setNextServoState(THREESTEPMOVEMENT2);
      setDisplayPicID(34); 
      break;
    case THREESTEPMOVEMENT2:
      setTargetPositionServo(10, 1, 160);
      setNextServoState(THREESTEPMOVEMENT3);
      break;
    case THREESTEPMOVEMENT3:
      setTargetPositionServo(10, 1, 85);
      setNextServoState(RETURN);
      break;
    case FLIPSWITCHBACKSLOW:
      setTargetPositionServo(30, 1, 85);
      setNextServoState(INACTIVE);
      setDisplayPicID(35);
      break;
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