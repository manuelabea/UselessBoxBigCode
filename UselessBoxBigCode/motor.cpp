#include "motor.h"


// Create an instance of the DRV8833:
DRV8833 driver = DRV8833();

// Pin numbers
const int inputA1 = 14, inputA2 = 15, inputB1 = 19, inputB2 = 18;
const int nsleep = 22;
volatile int speed;


void setUpMotor(){
  pinMode(nsleep, INPUT_PULLUP);
  digitalWrite(nsleep,HIGH); //enable Driver

  driver.attachMotorA(inputA1, inputA2);
  driver.attachMotorB(inputB1, inputB2);
  speed = 80;
}