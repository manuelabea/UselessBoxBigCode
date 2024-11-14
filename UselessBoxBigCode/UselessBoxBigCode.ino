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

unsigned long currentMillis;
unsigned long lastdebug;
int actionCounter = 0;

bool initialReturn = false;

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
    initialReturn = true;
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
    sensorInterruptedMethod();//checkSensor

  switchStates();
  checkActionState();
  checkServoState();
  checkLidState();
  checkLEDState();
  checkMotorState();
  checkDisplayState();

  if(millis()-lastdebug > 500){
    lastdebug=millis();
  Serial.print("lidState: ");
  Serial.print(getLidState());
  Serial.print(" - ServoState: ");
  Serial.print(getServoState());
  Serial.print(" - currentActionStep: ");
  Serial.print(getCurrentActionStep());
  Serial.print(" - finishedPrevStep ");
  Serial.println(getfinishedPrevStep());
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
      //Serial.print("nothing here");
      //Serial.println(actionCounter);
      if(initialReturn ==  true){
        setServoState(RETURN);
        setLidState(CLOSELID);
        initialReturn = false;
      }
      setToggleState(WAITING);
      setLEDState(BLUE);
      //setActionState(UNTOGGLED_ACTION1);
      setRandomUntoggledActionState();

      break;

    case TOGGLED:
      actionCounter++;
      //Serial.print("actionCounter: "); Serial.println(actionCounter);
      //setLidState(OPENLID);
      setLEDState(RED);
      //setActionState(ACTION6);
      setRandomActionState();
      setToggleState(WAITING);
      break;

    case WAITING:
      break;
  }

}

