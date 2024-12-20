/*
 * DRV8833_Test_2
 * Two-motor test for the DRV8833 library.
 * The DRV8833 is a dual motor driver carrier made by Pololu.
 * You can find it here: https://www.pololu.com/product/2130
 *
 * Attach the positive wire of a motor to the Aout1 and the negative
 * wire to the Aout2 pins on the DRV8833.
 * Attach the positive wire of a motor to the Bout1 and the negative
 * wire to the Bout2 pins on the DRV8833.
 * Attach the Arduino's ground to the one of the GND pins on the DRV8833.
 * Attach a 9V battery's positive connection to the Vin pin
 * on the DRV8833, and the negative connection to one of the GND pins.
 * 
 * Created March 31, 2015, by Aleksandr J. Spackman.
 */

#include <DRV8833.h>

// Create an instance of the DRV8833:
DRV8833 driver = DRV8833();

// Pin numbers. Replace with your own!
// Attach the Arduino's pin numbers below to the
// Ain1, Ain2, Bin1, and Bin2 DRV8833 pins.
const int inputA1 = 15, inputA2 = 14, inputB1 = 37, inputB2 = 36;

void setup() {
  // put your setup code here, to run once:
  
  // Start the serial port:
  Serial.begin(9600);
  
  // Wait for the serial port to connect. Needed for Leonardo.
  while (!Serial);
  
  // Attach the motors to the input pins:
  driver.attachMotorA(inputA1, inputA2);
  driver.attachMotorB(inputB1, inputB2);
  Serial.println("Ready!");

}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("Forward:");
  // Put the motors in forward:
  driver.motorAForward();
  driver.motorBForward();
  // Wait to see the effect:
  delay(500);
  
  // Pause the motors for stability:
  driver.motorAStop();
  driver.motorBStop();
  
  Serial.println("Reverse:");
  // Put the motors in reverse:
  driver.motorAReverse();
  driver.motorBReverse();
  // Wait to see the effect:
  delay(500);
  
  Serial.println("Stop:");
  // Stop the motors:
  driver.motorAStop();
  driver.motorBStop();
  // Wait to see the effect:
  delay(500);

}
