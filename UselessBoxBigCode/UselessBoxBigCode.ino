#include <Arduino.h>
#include <Bounce2.h>
#include <Servo.h>
#include "FastLED.h"
#include <DRV8833.h>

/*TOGGLE************************************************************************/
Bounce bounceToggle = Bounce();
bool toggled;
const int togglePin = 36;

enum states_t {
  TOGGLED,
  UNTOGGLED,
  WAITING
};
states_t state; // global variable to store current state

/*SERVO ToggleArm************************************************************************/
Servo toggleArm;
int pos ;                 // current servo position 
int increment = 0;            // increment to move for each interval
int updateInterval = 0;      // interval between updates
unsigned long lastUpdateServo; // last update of position
int nextPos; 
int endPos;  

enum servoStates_t {
  INACTIVE,
  MOVINGSERVO,
  FLIPSWITCHBACK, 
  FLIPSWITCHBACK2,
  RETURN,
  THREESTEPMOVEMENT1,
  THREESTEPMOVEMENT2,
  THREESTEPMOVEMENT3,
  FLIPSWITCHBACKSLOW
  
};
servoStates_t servoState;
servoStates_t nextServoState;

/*SERVO Lid************************************************************************/
Servo lid;
int posLid ;                 // current servo position 
int incrementLid = 0;            // incrementLid to move for each interval
int updateIntervalLid = 0;      // interval between updates
unsigned long lastUpdateLid; // last update of position
int nextPosLid; 
int endPosLid;  

enum lidStates_t {
  INACTIVELID,
  MOVINGLID,
  OPENLID,
  CLOSELID  
};
lidStates_t lidState;
lidStates_t nextLidState;

/*Sensor************************************************************************/
const int sensorPin = 12;

bool sensorInterrupted;
volatile int sensorState;
volatile int oldSensorState;

/*LED************************************************************************/
const int ledPin = 32;

#define LED_TYPE    NEOPIXEL
#define COLOR_ORDER GRB
#define NUM_LEDS    6
CRGB leds[NUM_LEDS];
#define BRIGHTNESS 123
#define FRAMES_PER_SECOND  120

uint8_t hue;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

enum ledStates_t {
  NOLED,
  RED,
  GREEN,
  BLUE
};
ledStates_t ledState;

/*Motor************************************************************************/
// Create an instance of the DRV8833:
DRV8833 driver = DRV8833();

// Pin numbers
const int inputA1 = 14, inputA2 = 15, inputB1 = 19, inputB2 = 18;
const int nsleep = 22;
volatile int speed;

/*ACTIONS************************************************************************/
enum actionStates_t {
  NOACTION,
  ACTION1,
  ACTION2,
  ACTION3,
  FINISHEDACTION
};
actionStates_t actionState;

int currentActionStep;
bool finishedPrevStep;

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

  state = WAITING;
  servoState = INACTIVE;

  attachInterrupt(digitalPinToInterrupt(togglePin), toggleToggled, CHANGE);

  pinMode(sensorPin, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(sensorPin), sensorInterrupt, CHANGE);

  FastLED.addLeds<NEOPIXEL, 32>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  toggleArm.attach(29); 
  toggleArm.write(170);

  lid.attach(25); 
  lid.write(110);

  if(bounceToggle.read() == HIGH){
    servoState = FLIPSWITCHBACK;
  }
  
  pinMode(nsleep, INPUT_PULLUP);
  digitalWrite(nsleep,HIGH); //enable Driver

  driver.attachMotorA(inputA1, inputA2);
  driver.attachMotorB(inputB1, inputB2);
  speed = 80;

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
      state = TOGGLED;
      //Serial.print("actionCounter:"); Serial.println (actionCounter);
    } else {
      state = UNTOGGLED;
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
  switch (state){
    case UNTOGGLED:
      Serial.print("nothing here");
      Serial.println(actionCounter);
      servoState = RETURN;
      lidState = CLOSELID;
      state = WAITING;
      ledState = BLUE;

      break;

    case TOGGLED:
      actionCounter++;
      Serial.print("actionCounter: "); Serial.println(actionCounter);
      lidState = OPENLID;
      ledState = RED;
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
      actionState = ACTION1;
      state = WAITING;
      break;

    case WAITING:
      break;
  }

}

void checkActionState(){
  switch(actionState) {
    case NOACTION:
      currentActionStep = 0;
      break;    
    case ACTION1:
      if (currentActionStep == 0) {
        finishedPrevStep = false;
        lidState = OPENLID;
        currentActionStep++;
        break;
      } else if (currentActionStep == 1 && finishedPrevStep == true) {
        finishedPrevStep = false;
        servoState = THREESTEPMOVEMENT1;
        actionState = NOACTION;
        break;
      } 
    }
}

void checkServoState(){
  pos = constrain(pos, 85, 170);
  switch (servoState) {
    case INACTIVE:
      break;
    case MOVINGSERVO:
      movement();
      break;
    case FLIPSWITCHBACK:
      setTargetPositionServo(10, 1, 170);
      setTargetPositionServo(10, 1, 85);
      setDisplayPicID(36);
      nextServoState = INACTIVE;
      break;
    case RETURN:
      setTargetPositionServo(10, 1, 170);
      setDisplayPicID(33);
      break;
    case THREESTEPMOVEMENT1:
      setTargetPositionServo(10, 1, 130);
      nextServoState = THREESTEPMOVEMENT2;
      setDisplayPicID(34); 
      break;
    case THREESTEPMOVEMENT2:
      setTargetPositionServo(10, 1, 160);
      nextServoState = THREESTEPMOVEMENT3;
      break;
    case THREESTEPMOVEMENT3:
      setTargetPositionServo(10, 1, 85);
      nextServoState = RETURN;
      break;
    case FLIPSWITCHBACKSLOW:
      setTargetPositionServo(30, 1, 85);
      nextServoState = INACTIVE;
      setDisplayPicID(35);
      break;
  }
}

void checkLidState(){
  posLid = constrain(posLid, 85, 180);
  switch (lidState) {
    case INACTIVELID:
      break;
    case MOVINGLID:
      movementLid();
      break;
    case OPENLID:
      setTargetPositionLid(10, 1, 180);
      setDisplayPicID(36);
      nextLidState = INACTIVELID;
      break;
    case CLOSELID:
      setTargetPositionLid(10, 1, 110);
      setDisplayPicID(33);
      break;
  }
}

void checkLEDState(){
  switch (ledState) {
    case NOLED:
      FastLED.clear();
      FastLED.show();  // display the pixels
      break;
    case RED:
      fill_solid( leds, NUM_LEDS, CHSV(0,255,255) );  //set color of pixels - red
      FastLED.show();  // display the pixels
      break;
    case GREEN:
      fill_solid( leds, NUM_LEDS, CHSV(90,255,255) );  //set color of pixels - green
      FastLED.show();  // display the pixels
      break;
    case BLUE:
      fill_solid( leds, NUM_LEDS, CHSV(160,255,255) );  //set color of pixels - blue
      FastLED.show();  // display the pixels
      break;
  }
}

void setTargetPositionServo(int _updateInterval, int _increment, int _endPos){

  updateInterval = _updateInterval;
  increment = _increment;
  endPos = _endPos;
  servoState = MOVINGSERVO;

}

void setTargetPositionLid(int _updateIntervalLid, int _incrementLid, int _endPosLid){

  updateIntervalLid = _updateIntervalLid;
  incrementLid = _incrementLid;
  endPosLid = _endPosLid;
  lidState = MOVINGLID;

}

void movement(){
  if((millis() - lastUpdateServo) > updateInterval){  // time to update
    lastUpdateServo = millis();

    if (pos > endPos){
      pos -= increment;
    } else {
      pos += increment;
    } 
    toggleArm.write(pos);
    state = WAITING; 
    
    if(pos == endPos) {
      finishedPrevStep = true;
      if (nextServoState != INACTIVE) {
        servoState = nextServoState;
      } else {
        servoState = INACTIVE;
      }
    }
  }
}

void movementLid(){
  if((millis() - lastUpdateLid) > updateIntervalLid){  // time to update
    lastUpdateLid = millis();

    if (posLid > endPosLid){
      posLid -= incrementLid;
    } else {
      posLid += incrementLid;
    } 
    lid.write(posLid);
    state = WAITING; 

    Serial.print("posLid: ");
    Serial.print(posLid);
    Serial.print(" - endPosLid: ");
    Serial.println(endPosLid);
    
    if(posLid == endPosLid) {
      finishedPrevStep = true;
      if (nextLidState != INACTIVELID) {
        lidState = nextLidState;
      } else {
        lidState = INACTIVELID;
      }
    }
  }
}

void setDisplayPicID(int _picID) {
  Serial1.print("p0.pic=");Serial1.print(_picID);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff); 
}

void lightUp(){
  if (sensorState == HIGH) { //
    ledState = NOLED;
  }
  if (sensorState == LOW) { //
    ledState = GREEN;
  }
}