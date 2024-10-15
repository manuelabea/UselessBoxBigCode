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

void setFinishedPrevStep(bool _finishedPrevStep){
  finishedPrevStep = _finishedPrevStep;
}

void checkActionState(){
  switch(actionState) {
    case NOACTION:
      currentActionStep = 0;
      break;    
    case ACTION1:
      if (currentActionStep == 0) {
        finishedPrevStep = false;
        setLidState(OPENLID);
        currentActionStep++;
        break;
      } else if (currentActionStep == 1 && finishedPrevStep == true) {
        finishedPrevStep = false;
        setServoState(THREESTEPMOVEMENT1);
        actionState = NOACTION;
        break;
      } 
    }
}