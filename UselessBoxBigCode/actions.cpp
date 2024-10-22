#include "actions.h"

actionStates_t actionState;


int currentActionStep;
bool finishedPrevStep;

void setActionState(actionStates_t _state){
  actionState = _state;
}

actionStates_t getActionState(){
  return actionState;
}

bool getfinishedPrevStep(){
  return finishedPrevStep;
}
/*
int getActionCounter(){
  return actionCounter;
}

void setActionCounter(int _newActionCounter){
  actionCounter = _newActionCounter;
}
*/
void setFinishedPrevStep(bool _finishedPrevStep){
  finishedPrevStep = _finishedPrevStep;
}

void checkActionState(){
  switch(actionState) {
    case NOACTION:
      currentActionStep = 0;
      finishedPrevStep = false;
      break;    
    case ACTION1://////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if (currentActionStep == 0) {
        finishedPrevStep = false;
        setLidState(OPENLID);
        currentActionStep++;
        break;
      } else if (currentActionStep == 1 && finishedPrevStep == true) {
        finishedPrevStep = false;
        setServoState(THREESTEPMOVEMENT1);
        actionState = NOACTION;
        //Serial.println("Blub");
        break;
      }
    case ACTION2://////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (currentActionStep == 0) {
          finishedPrevStep = false;
          setLidState(RATTLELID);
          currentActionStep++;
          break;
      } else if (currentActionStep == 1 && finishedPrevStep == true) {
          finishedPrevStep = false;
          setServoState(FLIPSWITCHBACK);
          actionState = NOACTION;
          //Serial.println("Blub");
          break;
      }
    case UNTOGGLED_ACTION1://////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if (currentActionStep == 0) {
        attachSensor();
        attachMotor();
        currentActionStep++;
        break;
      } else if (currentActionStep == 1) {
        Serial.println(getInterruptedByUser());
        if (getInterruptedByUser() > 3){
          Serial.println("Blub");
          detachSensor();
          currentActionStep++;
        }
        break;
      } else if (currentActionStep == 2){
        actionState = NOACTION;
        break;
      }
    case UNTOGGLED_ACTION2://////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if (currentActionStep == 0) {
        attachSensor();
        attachMotor();
        currentActionStep++;
        break;
      } else if (currentActionStep == 1) {
        Serial.println(getInterruptedByUser());
        if (getInterruptedByUser() > 2 & getFinishedMotorStep() == true){
          //Serial.println("got here?");
          detachSensor();
          currentActionStep++;
        }
        break;
      } else if (currentActionStep == 2){
        actionState = NOACTION;
        break;
      }
  }
}