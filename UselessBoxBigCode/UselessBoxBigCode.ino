#include <Arduino.h>
#include <Bounce2.h>

#include "led.h"
#include "toggle.h"
#include "myservo.h"
#include "actions.h"
#include "myLidServo.h"
#include "display.h"
#include "motor.h"
#include "sensor.h"

/*TOGGLE************************************************************************/
Bounce bounceToggle = Bounce();
bool toggled;
const int togglePin = 36;

/*OTHER************************************************************************/
int actionCounter = 0;
unsigned long currentMillis;
unsigned long lastdebug;

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

  //attachInterrupt(digitalPinToInterrupt(togglePin), toggleToggled, CHANGE);
  
  setUpSensor();

  setUpLED();

  setUpToggleArm();
  setUpLid();
  

  if(bounceToggle.read() == HIGH){
    setServoState(FLIPSWITCHBACK);
  }
  
  setUpMotor();

}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  
  //if (toggled == true) {
    debouncerMethod();
  //}
  if (getSensorInterruptedState() == true) {
    sensorInterruptedMethod();
  }
  switchStates();
  checkActionState();
  checkServoState();
  checkLidState();
  checkLEDState();

  if(millis()-lastdebug > 500){
    lastdebug=millis();
  /*Serial.print("lidState: ");
  Serial.print(getLidState());
  Serial.print(" - ServoState: ");
  Serial.print(getServoState());
  Serial.print(" - currentActionStep: ");
  Serial.print(getActionState());
  Serial.print(" - finishedPrevStep ");
  Serial.println(getfinishedPrevStep());*/
  }

}

void toggleToggled(){
  toggled = true;
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

