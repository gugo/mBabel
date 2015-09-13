  // Shows how to run three Steppers at once with varying speeds
//
// Requires the Adafruit_Motorshield v2 library 
//   https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
// And AccelStepper with AFMotor support 
//   https://github.com/adafruit/AccelStepper

// This tutorial is for Adafruit Motorshield v2 only!
// Will not work with v1 shields

#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

#define M_COUNT 13
#define STEPMODE DOUBLE

Adafruit_MotorShield S0(0x60);
Adafruit_MotorShield S1(0x61); 
Adafruit_MotorShield S2(0x62);
Adafruit_MotorShield S3(0x63);
Adafruit_MotorShield S4(0x64);
Adafruit_MotorShield S5(0x65);
Adafruit_MotorShield S6(0x66);

Adafruit_MotorShield shields[7] = {S0,S1,S2,S3,S4,S5,S6};

Adafruit_StepperMotor *motor[M_COUNT];

AccelStepper *stepper[M_COUNT];

void initMotors() {

  int shieldAddress = 0;

  for(int i = 1; i <= M_COUNT; i++) {

    shieldAddress = int(i/2);

    if(i%2==0){
      motor[i] = shields[shieldAddress].getStepper(200,1);
    } else {
      motor[i] = shields[shieldAddress].getStepper(200,2);
    }

    Adafruit_StepperMotor *mt = motor[i];
    AccelStepper *sp = new AccelStepper( mt , STEPMODE);
    stepper[i] = sp;
  } 
}
  
// void setup() {  
//   initMotors(); 

//   for(int i=0; i<7; i++){
//     shields[i].begin();
//   }

//   for(int i=1; i<=M_COUNT; i++){
//     stepper[i]->setSpeed(180);
//   }
// }

// void loop() {
//   for(int i=1; i<=M_COUNT; i++){
//     stepper[i]->runSpeed();
//   }
// }

// AccelStepper *sp;
// AccelStepper *sp2;
// AccelStepper *sp3;

void setup()
{
  S0.begin();
  S1.begin();
  S2.begin();
  S3.begin();
  S4.begin();
  S5.begin(); 
  S6.begin();
  
  int shieldAddress = 0;

  for(int i = 1; i <= M_COUNT; i+=2) {

    shieldAddress = int(i/2);

    // shields[shieldAddress].begin();

    
    motor[i] = shields[shieldAddress].getStepper(200,1);
    motor[i+1] = shields[shieldAddress].getStepper(200,2);
    
    stepper[i] =  new AccelStepper( motor[i] , STEPMODE);
    stepper[i]->setSpeed(180);
    stepper[i] =  new AccelStepper( motor[i] , STEPMODE);
    stepper[i+1]->setSpeed(180); 
  } 
}

void loop()
{
  stepper[1]->runSpeed();
}

