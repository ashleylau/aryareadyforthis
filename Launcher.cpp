#include "Launcher.h"
#include <Arduino.h>
#include <Servo.h>
#include <PWMServo.h>

/*----------Global Variables----------*/
int servoStop = 1500;
int servoCC   = 1350;
int servoCW   = 1650; 
int flywheelGo = 1;
int flywheelStop = 0;


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
Function:     moveServo
Contents:     This function is used to rotate the servo ata low speed.
Parameters:   None; if later set to move at different speeds this can be included.
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::moveServo(){
    myservo.writeMicroseconds(1600);
}

/******************************************************************************
Function:     clearSwitch
Contents:     This function is used to rotate the servo enough to clear the limit switch.
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::clearSwitch(){
    moveServo();
    delay(150);
    stopServo();
}

/******************************************************************************
Function:     shootBall
Contents:     This function is used to rotate the servo enough to shoot one ball.
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::shootBall(){
    moveServo();
    while(!digitalRead(LIMIT_SERVO)){
    //wait
    }
    stopServo();
}

/******************************************************************************
Function:     stopServo
Contents:     This function is used to stop the rotatation of the servo.
Parameters:   None; if later set to move at different speeds this can be included.
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::stopServo(){
    myservo.writeMicroseconds(1500);
}

/******************************************************************************
Function:     powerServo
Contents:     This function is used to give power to servo, causes jerk.
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::powerServo(){
    digitalWrite(SERVO_MOSFET, HIGH);
}

/******************************************************************************
Function:     turnOffServo
Contents:     This function is used to cut all power to servo.
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::turnOffServo(){
    digitalWrite(SERVO_MOSFET, LOW);
}

/*----------Private Functions---------*/
//Private function to initialize pins when the motor class is first included
void LauncherClass::begin( ) { 
  //  Set up the pin modes
  pinMode(FLYWHEEL, OUTPUT);
  pinMode(SERVO_LOGIC, OUTPUT);
  pinMode(SERVO_MOSFET, OUTPUT);
  pinMode(LIMIT_SERVO, INPUT_PULLUP);

  digitalWrite(SERVO_MOSFET, LOW);

  //Set up servo
  myservo.attach(SERVO_LOGIC, 1000, 2000);
  myservo.writeMicroseconds(1500);
}