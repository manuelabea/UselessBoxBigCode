#include "actions.h"

actionStates_t actionState;


int currentActionStep;
bool finishedPrevStep;
unsigned long startedActionTimestamp;
unsigned long currentMillisAction;

actionStates_t randomActions[ ] = {ACTION1, ACTION2, ACTION3, ACTION4, ACTION5, ACTION6};
int randomAction;
int number_of_stored_values_in_randomActions = sizeof(randomActions)/sizeof(actionStates_t);

actionStates_t randomUntoggledActions[ ] = {NOACTION, UNTOGGLED_ACTION1, UNTOGGLED_ACTION2, UNTOGGLED_ACTION3};
int randomUntoggledAction;
int number_of_stored_values_in_randomUntoggledActions = sizeof(randomUntoggledActions)/sizeof(actionStates_t);


void setRandomActionState(){
  randomAction = random(0,number_of_stored_values_in_randomActions);
  actionState = randomActions[randomAction];
  //Serial.print("Random State: "); Serial.println(actionState);
}

void setRandomUntoggledActionState(){
  randomUntoggledAction = random(0,number_of_stored_values_in_randomUntoggledActions);
  actionState = randomUntoggledActions[randomUntoggledAction];
  Serial.print("Random (untoggled) State: "); Serial.println(actionState);
}

void resetActionStepAndFinishedPrevStep(){
  currentActionStep = 0;
  setFinishedPrevStep(true);
}

void setActionState(actionStates_t _state){
  actionState = _state;
}

actionStates_t getActionState(){
  return actionState;
}

int getCurrentActionStep(){
  return currentActionStep;
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
        setDisplayPicID(25);
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
          setDisplayPicID(28);
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
    case ACTION3:
      if (currentActionStep == 0 ) {
        finishedPrevStep = false;
        setDisplayPicID(31);
        attachMotor();
        setTimePassedSinceMotorStart();
        setMotorState(REVERSE_TIMED);
        currentActionStep++;
        break;
      } else if (currentActionStep == 1 && finishedPrevStep == true) {
        finishedPrevStep = false;
        setServoState(FLIPSWITCHBACK);
        actionState = NOACTION;
        break;
      }
    case ACTION4://////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if (currentActionStep == 0 ) {
        finishedPrevStep = false;
        setDisplayPicID(4);
        attachMotor();
        setTimePassedSinceMotorStart();
        setMotorState(FORWARD_TIMED);
        currentActionStep++;
        break;
      } else if (currentActionStep == 1 && finishedPrevStep == true) {
        finishedPrevStep = false;
        setServoState(FLIPSWITCHBACK);
        actionState = NOACTION;
        break;
      }
    case ACTION5://////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if (currentActionStep == 0) {
        finishedPrevStep = false;
        setLidState(OPENLIDVERYSLOW);
        setDisplayPicID(25);
        currentActionStep++;
        break;
      } else if (currentActionStep == 1 && finishedPrevStep == true) {
        finishedPrevStep = false;
        setServoState(FLIPSWITCHBACKVERYSLOW);
        actionState = NOACTION;
        //Serial.println("Blub");
        break;
      }
    case ACTION6://////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if(currentActionStep == 0){
        finishedPrevStep = false;
        setDisplayChangeTimestamp();
        setDisplayState(DISPLAYSHOWING_HOMERGIF);
        currentActionStep++;
      }
      else if (currentActionStep == 1 && finishedPrevStep == true) {
        finishedPrevStep = false;
        setLidState(OPENLID);
        //setDisplayPicID(25);
        currentActionStep++;
      } else if (currentActionStep == 2 && finishedPrevStep == true) {
        finishedPrevStep = false;
        setDisplayPicID(25);
        setServoState(FLIPSWITCHBACKSLOW);
        actionState = NOACTION;
        Serial.println("Blub");
      }
      break;
    case UNTOGGLED_ACTION1://////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if (currentActionStep == 0) {
        //setDisplayPicID(38);
        setServoState(RETURN);
        setLidState(CLOSELID);
        attachSensor();
        attachMotor();
        currentActionStep++;
      } else if (currentActionStep == 1) {
        //Serial.println(getInterruptedByUser());
        if (getInterruptedByUser() > 3){
          //Serial.println("Blub");
          detachSensor();
          currentActionStep++;
        }
      } else if (currentActionStep == 2){
        actionState = NOACTION;
        
      }
      break;
    case UNTOGGLED_ACTION2://////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if (currentActionStep == 0) {
        setDisplayPicID(33);
        attachSensor();
        attachMotor();
        currentActionStep++;
      } else if (currentActionStep == 1) {
        //Serial.println(getInterruptedByUser());
        if (getInterruptedByUser() > 2 & getFinishedMotorStep() == true){
          //Serial.println("got here?");
          detachSensor();
          currentActionStep++;
        }
      } else if (currentActionStep == 2){
        actionState = NOACTION;
      }
      break;
    case UNTOGGLED_ACTION3://////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if (currentActionStep == 0) {
        finishedPrevStep = false;
        setServoState(RETURNVERYSLOW);
        setDisplayChangeTimestamp();
        setDisplayPicID(25);
        currentActionStep++;
      } else if (currentActionStep == 1 && finishedPrevStep == true) {
        finishedPrevStep = false;
        setLidState(CLOSELID);
        actionState = NOACTION;
        Serial.println("Blub");
      }
      break;
    case UNTOGGLED_ACTION4://////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      if (currentActionStep == 0) {
        finishedPrevStep = false;
        attachMotor();
        setTimePassedSinceMotorStart();
        setMotorState(ONEEIGHTY_TIMED); 
        currentActionStep++;
      }
      else if (currentActionStep == 1) {
        finishedPrevStep = false;
        //setDisplayPicID(38);
        setServoState(RETURN);
        setLidState(CLOSELID);
        currentActionStep++;
      } else if (currentActionStep == 2){
        actionState = NOACTION;
        
      }
      break;
  }
}