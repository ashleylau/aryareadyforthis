#include "Launcher.h"
#include <Arduino.h>
#include <Servo.h>
#include <PWMServo.h>

/*----------Global Variables----------*/
int flywheelGo = 1;
int flywheelStop = 0;
int angle = 38;

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
    digitalWrite(FLYWHEEL, flywheelGo);
}

/******************************************************************************
Function:     stopFlywheel
Contents:     Stop motor so flywheel stops spinning.
Parameters:   None; if later set to move at different speeds this can be included.
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::stopFlywheel(){
    digitalWrite(FLYWHEEL, flywheelStop);
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

/******************************************************************************
Function:     resetBall
Contents:     This function is used to return the rotater to its starting position.
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::returnRotator(){
    myservo.write(-270);
}

/*----------Private Functions---------*/
//Private function to initialize pins when the motor class is first included
void LauncherClass::begin( ) { 
  Serial.begin(9600);

  //  Set up the pin modes
  pinMode(FLYWHEEL, OUTPUT);
  pinMode(SERVO, OUTPUT);

  //Set up servo
  myservo.attach(SERVO);
}