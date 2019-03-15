#include "Launcher.h"
#include <Arduino.h>
#include <PWMServo.h>

/*----------Global Variables----------*/
int flywheelGo = 1;
int flywheelStop = 0;
int loaderGo = 1;
int loaderStop = 0;

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
void LauncherClass::startFlywheel()
{
    digitalWrite(FLYWHEEL, flywheelGo);
}

/******************************************************************************
Function:     stopFlywheel
Contents:     Stop motor so flywheel stops spinning.
Parameters:   None; if later set to move at different speeds this can be included.
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::stopFlywheel()
{
    digitalWrite(FLYWHEEL, flywheelStop);
}

/******************************************************************************
Function:     moveServo
Contents:     This function is used to rotate the servo ata low speed.
Parameters:   None; if later set to move at different speeds this can be included.
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::moveServo()
{
    digitalWrite(LOADER_MOSFET, loaderGo);
}

/******************************************************************************
Function:     clearSwitch
Contents:     This function is used to rotate the servo enough to clear the limit switch.
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void LauncherClass::clearSwitch()
{
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
void LauncherClass::shootBall()
{
    moveServo();
    while (!digitalRead(LIMIT_SERVO))
    {
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
void LauncherClass::stopServo()
{
    digitalWrite(LOADER_MOSFET, loaderStop);
}

/*----------Private Functions---------*/
//Private function to initialize pins when the motor class is first included
void LauncherClass::begin()
{
    //  Set up the pin modes
    //Serial.begin(9600);

    pinMode(FLYWHEEL, OUTPUT);
    pinMode(LOADER_MOSFET, OUTPUT);
    pinMode(LIMIT_SERVO, INPUT_PULLUP);

    digitalWrite(LOADER_MOSFET, LOW);

    //Set up servo
}