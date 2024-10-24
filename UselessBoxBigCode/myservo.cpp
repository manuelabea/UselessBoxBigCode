#include "myservo.h";


Servo toggleArm;
int pos; //= constrain(pos, 85, 170);                // current servo position 
int increment = 0;            // increment to move for each interval
int updateInterval = 0;      // interval between updates
unsigned long lastUpdateServo; // last update of position
int nextPos; 
int endPos;

  
servoStates_t servoState;
servoStates_t nextServoState;

void setUpToggleArm(){
  toggleArm.attach(29); 
  toggleArm.write(170);
  pos = 170;

}

void setServoState(servoStates_t _state){
  servoState = _state;
}
servoStates_t getServoState(){
  return servoState;
}

void setNextServoState(servoStates_t _nextState){
  nextServoState = _nextState;
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
    setToggleState(WAITING); 
    
    if(pos == endPos) {
      setFinishedPrevStep(true);
      if (nextServoState != INACTIVE) {
        servoState = nextServoState;
      } else {
        servoState = INACTIVE;
      }
    }
  }
}

void setTargetPositionServo(int _updateInterval, int _increment, int _endPos){

  updateInterval = _updateInterval;
  increment = _increment;
  endPos = _endPos;
  setServoState(MOVINGSERVO);

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
      setNextServoState(INACTIVE);
      break;
    case RETURN:
      setTargetPositionServo(10, 1, 170);
      setNextServoState(INACTIVE);
      break;
    case RETURNVERYSLOW:
      setTargetPositionServo(50, 1, 170);
      setNextServoState(INACTIVE);
    case THREESTEPMOVEMENT1:
      setTargetPositionServo(10, 1, 130);
      setNextServoState(THREESTEPMOVEMENT2);
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
      break;
    case FLIPSWITCHBACKVERYSLOW:
      setTargetPositionServo(50, 1, 85);
      setNextServoState(INACTIVE);
      break;
  }
  
}