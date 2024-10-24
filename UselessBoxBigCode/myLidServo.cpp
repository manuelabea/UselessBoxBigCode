#include "myLidServo.h"

Servo lid;
int posLid; //= constrain(posLid, 85, 180);                 // current servo position 
int incrementLid = 0;            // incrementLid to move for each interval
int updateIntervalLid = 0;      // interval between updates
unsigned long lastUpdateLid; // last update of position
int nextPosLid; 
int endPosLid;  


lidStates_t lidState;
lidStates_t nextLidState;

int rattleCounter;

void setUpLid(){
  lid.attach(25); 
  lid.write(110);
  posLid = 110;
}

void setLidState(lidStates_t _state){
  lidState = _state;
}

lidStates_t getLidState(){
  return lidState;
}

void setNextLidState(lidStates_t _nextLidState){
  nextLidState = _nextLidState;
}

void checkLidState(){
  
  switch (lidState) {
    case INACTIVELID:
      break;
    case FINISHEDSTEP:
      setFinishedPrevStep(true);
      setNextLidState(INACTIVELID);
      break;
    case MOVINGLID:
      movementLid();
      break;
    case OPENLID:
      setTargetPositionLid(10, 1, 180);
      setDisplayPicID(36);
      setNextLidState(FINISHEDSTEP);
      break;
    case OPENLIDVERYSLOW: 
      setTargetPositionLid(50, 1, 180);
      setNextLidState(FINISHEDSTEP);
      break;
    case CLOSELID:
      setTargetPositionLid(10, 1, 110);
      setDisplayPicID(33);
      break;
    case RATTLELID:
      rattleCounter=0;
      setNextLidState(RATTLELID_OPEN);
    case RATTLELID_OPEN:
      setTargetPositionLid(2, 1, 180);
      if (rattleCounter < random(1, 3)){
        rattleCounter++;
        setNextLidState(RATTLELID_CLOSE);
      } else {
        setNextLidState(FINISHEDSTEP);
      }
      break;
    case RATTLELID_CLOSE:
      setTargetPositionLid(2, 1, 150);
      setNextLidState(RATTLELID_OPEN);
      break;      
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
    setToggleState(WAITING); 

    /*Serial.print("posLid: ");
    Serial.print(posLid);
    Serial.print(" - endPosLid: ");
    Serial.println(endPosLid);*/
    
    if(posLid == endPosLid) {
      
      if (nextLidState != INACTIVELID) {
        lidState = nextLidState;
      } else {
        lidState = INACTIVELID;
      }
    }
  }
}

void setTargetPositionLid(int _updateIntervalLid, int _incrementLid, int _endPosLid){

  updateIntervalLid = _updateIntervalLid;
  incrementLid = _incrementLid;
  endPosLid = _endPosLid;
  lidState = MOVINGLID;

}