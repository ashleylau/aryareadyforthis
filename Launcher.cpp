#include "Launcher.h"
#include <Arduino.h>
#include <Servo.h>
#include <PWMServo.h>

/*----------Global Variables----------*/
int dir1 = LOW;
int dir2 = HIGH;
int flywheelSpeed = 255;
int flywheelStop = 0;
int angle = 52;

Servo myservo;

LauncherClass launcher;

/*----------Public Functions---------*/

LauncherClass::LauncherClass()
{
    begin();
}
/******************************************************************************
Function:     startFlywheel
Contents:     Spin motor forward so will shoot balls when they fall.
Parameters:   None; if later set to move at different speeds this can be included.
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::startFlywheel(){
    digitalWrite(FLYWHEEL_DIR1, dir1);
    digitalWrite(FLYWHEEL_DIR2, dir2);
    analogWrite(FLYWHEEL_ENABLE, flywheelSpeed);
}

/******************************************************************************
Function:     stopFlywheel
Contents:     Stop motor so flywheel stops spinning.
Parameters:   None; if later set to move at different speeds this can be included.
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::stopFlywheel(){
    analogWrite(FLYWHEEL_ENABLE, flywheelStop);
}

/******************************************************************************
Function:     incrementBall
Contents:     This function is used to rotate the servo a seventh of the way to release ball.
Parameters:   None; if later set to move at different speeds this can be included.
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::incrementBall(){
    myservo.write(angle);
}

/*----------Private Functions---------*/
//Private function to initialize pins when the motor class is first included
void LauncherClass::begin( ) { 
  Serial.begin(9600);

  //  Set up the pin modes
  pinMode(FLYWHEEL_ENABLE, OUTPUT);
  pinMode(FLYWHEEL_DIR1, OUTPUT);
  pinMode(FLYWHEEL_DIR2, OUTPUT);
  pinMode(SERVO, OUTPUT);

  //Set up servo
  myservo.attach(SERVO);
}