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