#include "motor.h"


// Create an instance of the DRV8833:
DRV8833 driver = DRV8833();

// Pin numbers
const int inputA1 = 14, inputA2 = 15, inputB1 = 19, inputB2 = 18;
const int nsleep = 22;
volatile int speed;

motorStates_t motorState;

unsigned long timePassedSinceMotorStart;
int currentMotorActionStep = 0;
bool finishedMotorStep;

int randomDirection;

bool getFinishedMotorStep() {
  return finishedMotorStep;
}

void setMotorState(motorStates_t _motorState) {
  motorState = _motorState;
}

motorStates_t getMotorState() {
  return motorState;
}

unsigned long getTimePassedSinceMotorStart() {
  return timePassedSinceMotorStart;
}

void setTimePassedSinceMotorStart() {
  timePassedSinceMotorStart = millis();
}

void setUpMotor() {
  pinMode(nsleep, INPUT_PULLUP);
  driver.attachMotorA(inputA1, inputA2);
  driver.attachMotorB(inputB1, inputB2);
  speed = 80;
}

void detachMotor() {
  digitalWrite(nsleep, LOW);
}

void attachMotor() {
  digitalWrite(nsleep, HIGH);
}

void driveMotor() {
  driver.motorAForward();
  driver.motorBForward();
}

void reverseMotor() {
  driver.motorAReverse();
  driver.motorBReverse();
}

/*void drive180AndAttack(){
  driver.motorAForward();
  if (startedDriving)
}
*/
void stopMotor() {
  driver.motorAStop();
  driver.motorBStop();
}

void forwardAReverseBMotor(){
  driver.motorAForward();
  driver.motorBReverse();
}
void reverseAForwardBMotor(){
  driver.motorAReverse();
  driver.motorBForward();
}

void setRandomDirection(){
  randomDirection = random(0,2);
}

void checkMotorState() {
  switch (motorState) {
    case NOMOTORACTION:
      currentMotorActionStep = 0;
      stopMotor();
      break;
    case FINISHEDMOTORSTEP:
      setFinishedPrevStep(true);
      setMotorState(NOMOTORACTION);
    case DRIVE180:
      if (currentMotorActionStep == 0) {
        finishedMotorStep = false;
        //Serial.println("got here");
        driver.motorAForward();
        driver.motorBReverse();
        currentMotorActionStep++;
        break;
      } else if (currentMotorActionStep == 1) {
        if ((millis() - timePassedSinceMotorStart) > 200) {
          stopMotor();
          currentMotorActionStep++;
        }
        break;
      } else if (currentMotorActionStep == 2) {
        //Serial.println("got HERE");
        setTimePassedSinceMotorStart();
        driveMotor();
        currentMotorActionStep++;
        break;
      } else if (currentMotorActionStep == 3) {
        //Serial.println("blub");
        if ((millis() - timePassedSinceMotorStart) > 400) {
          stopMotor();
          setMotorState(NOMOTORACTION);
          finishedMotorStep = true;
        }
        break;
      }
    case REVERSE_TIMED:
      if (currentMotorActionStep == 0) {
        finishedMotorStep = false;
        reverseMotor();
        currentMotorActionStep++;
      } else if (currentMotorActionStep == 1) {
        if ((millis() - timePassedSinceMotorStart) > 200) {
          stopMotor();
          setMotorState(FINISHEDMOTORSTEP);
          finishedMotorStep = true;
        }
        break;
      }
    case FORWARD_TIMED:
      if (currentMotorActionStep == 0) {
        finishedMotorStep = false;
        driveMotor();
        currentMotorActionStep++;
      } else if (currentMotorActionStep == 1) {
        if ((millis() - timePassedSinceMotorStart) > 200) {
          stopMotor();
          setMotorState(FINISHEDMOTORSTEP);
          finishedMotorStep = true;
        }
        break;
      }
    case JUSTDRIVE:
      if (currentMotorActionStep == 0) {
        finishedMotorStep = false;
        driveMotor();
        currentMotorActionStep++;
      } else if (currentMotorActionStep == 1) {
        if ((millis() - timePassedSinceMotorStart) > 300) {
          stopMotor();
          setMotorState(NOMOTORACTION);
          finishedMotorStep = true;
        }
      }
      break;
    case THREESIXTY_TIMED: 
      if (currentMotorActionStep == 0) {
        finishedMotorStep = false;
        setRandomDirection();
        if(randomDirection == 0) {
          forwardAReverseBMotor();
        } else if (randomDirection == 1){
          reverseAForwardBMotor();
        }
        currentMotorActionStep++;
      } else if (currentMotorActionStep == 1) {
        if ((millis() - timePassedSinceMotorStart) > 950) {
          stopMotor();
          setMotorState(FINISHEDMOTORSTEP);
          finishedMotorStep = true;
        }
        break;
      }
  }
}