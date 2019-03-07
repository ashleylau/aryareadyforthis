#include "Motors.h"
#include <Arduino.h>

/*----------Global Variables----------*/
int front_back_dir1 = LOW;
int front_back_dir2 = HIGH;
int left_right_dir1 = LOW;
int left_right_dir2 = HIGH;
int speed = 40;
int lowSpeed = 5; 
int stop = 0;

MotorsClass motors;

/*----------Public Functions---------*/

MotorsClass::MotorsClass()
{
    begin();
}
/******************************************************************************
Function:     moveForward
Contents:     This function is used to set both the forward and backward motors to spin
              in the forward direction, moving the robot forward in a straight line.
Parameters:   None; if later set to move at different speeds this can be included.
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::moveForward(){
    left_right_dir1 = HIGH;
    left_right_dir2 = LOW;
    digitalWrite(LEFT_RIGHT_DIR1, left_right_dir1);
    digitalWrite(LEFT_RIGHT_DIR2, left_right_dir2);
    analogWrite(FRONT_BACK_ENABLE, stop);
    analogWrite(LEFT_RIGHT_ENABLE, speed);
}

/******************************************************************************
Function:     moveBackward
Contents:     This function is used to set both the forward and backward motors to spin
              in the backward direction, moving the robot backwards in a straight line.
Parameters:   None; if later set to move at different speeds this can be included.
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::moveBackward(){
    left_right_dir1 = LOW;
    left_right_dir2 = HIGH;
    digitalWrite(LEFT_RIGHT_DIR1, left_right_dir1);
    digitalWrite(LEFT_RIGHT_DIR2, left_right_dir2);
    analogWrite(FRONT_BACK_ENABLE, stop);
    analogWrite(LEFT_RIGHT_ENABLE, speed);
}

/******************************************************************************
Function:     moveLeft
Contents:     This function is used to set the left and right motors to spin forward,
              moving the robot to the left. (if going right, switch HIGH/LOW)
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::moveLeft(){
    front_back_dir1 = LOW;
    front_back_dir2 = HIGH;
    digitalWrite(FRONT_BACK_DIR1, front_back_dir1);
    digitalWrite(FRONT_BACK_DIR2, front_back_dir2);
    analogWrite(FRONT_BACK_ENABLE, speed);
    analogWrite(LEFT_RIGHT_ENABLE, stop);
}

/******************************************************************************
Function:     rideBackWall
Contents:     This function is used to set the left and right motors to spin forward,
              moving the robot to the left. (if going right, switch HIGH/LOW)
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::rideBackWall(){
    front_back_dir1 = LOW;
    front_back_dir2 = HIGH;
    left_right_dir1 = LOW;
    left_right_dir2 = HIGH;
    digitalWrite(FRONT_BACK_DIR1, front_back_dir1);
    digitalWrite(FRONT_BACK_DIR2, front_back_dir2);
    digitalWrite(LEFT_RIGHT_DIR1, left_right_dir1);
    digitalWrite(LEFT_RIGHT_DIR2, left_right_dir2);
    analogWrite(FRONT_BACK_ENABLE, 55);
    analogWrite(LEFT_RIGHT_ENABLE, lowSpeed);
}

/******************************************************************************
Function:     rideFrontWallLeft
Contents:     This function is used to set the left and right motors to spin forward,
              moving the robot to the left. (if going right, switch HIGH/LOW)
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::rideFrontWallLeft(){
    front_back_dir1 = LOW;
    front_back_dir2 = HIGH;
    left_right_dir1 = HIGH;
    left_right_dir2 = LOW;
    digitalWrite(FRONT_BACK_DIR1, front_back_dir1);
    digitalWrite(FRONT_BACK_DIR2, front_back_dir2);
    digitalWrite(LEFT_RIGHT_DIR1, left_right_dir1);
    digitalWrite(LEFT_RIGHT_DIR2, left_right_dir2);
    analogWrite(FRONT_BACK_ENABLE, speed);
    analogWrite(LEFT_RIGHT_ENABLE, lowSpeed);
}

/******************************************************************************
Function:     rideFrontWallRight
Contents:     This function is used to set the left and right motors to spin forward,
              moving the robot to the right. (if going right, switch HIGH/LOW)
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::rideFrontWallRight(){
    front_back_dir1 = HIGH;
    front_back_dir2 = LOW;
    left_right_dir1 = HIGH;
    left_right_dir2 = LOW;
    digitalWrite(FRONT_BACK_DIR1, front_back_dir1);
    digitalWrite(FRONT_BACK_DIR2, front_back_dir2);
    digitalWrite(LEFT_RIGHT_DIR1, left_right_dir1);
    digitalWrite(LEFT_RIGHT_DIR2, left_right_dir2);
    analogWrite(FRONT_BACK_ENABLE, 40);
    analogWrite(LEFT_RIGHT_ENABLE, stop);
}

/******************************************************************************
Function:     moveRight
Contents:     This function is used to set the left and right motors to spin backwards
               moving the robot to the right.
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::moveRight(){
    front_back_dir1 = HIGH;
    front_back_dir2 = LOW;
    digitalWrite(FRONT_BACK_DIR1, front_back_dir1);
    digitalWrite(FRONT_BACK_DIR2, front_back_dir2);
    analogWrite(LEFT_RIGHT_ENABLE, stop);
    analogWrite(FRONT_BACK_ENABLE, 40);
}

/******************************************************************************
Function:     stopMotors
Contents:     This function is used to turn both motors off, stopping the robot.
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::stopMoving(){
    analogWrite(LEFT_RIGHT_ENABLE, stop);
    analogWrite(FRONT_BACK_ENABLE, stop);
}

/*----------Private Functions---------*/
//Private function to initialize pins when the motor class is first included
void MotorsClass::begin( ) { 
  //  Set up the pin modes
  pinMode(LEFT_RIGHT_ENABLE, OUTPUT);
  pinMode(LEFT_RIGHT_DIR1, OUTPUT);
  pinMode(LEFT_RIGHT_DIR2, OUTPUT);
  pinMode(FRONT_BACK_ENABLE, OUTPUT);
  pinMode(FRONT_BACK_DIR1, OUTPUT);
  pinMode(FRONT_BACK_DIR2, OUTPUT);

  //  Set the speeds and directions to initial values
  digitalWrite(LEFT_RIGHT_DIR1, left_right_dir1);
  digitalWrite(LEFT_RIGHT_DIR2, left_right_dir2);
  digitalWrite(FRONT_BACK_DIR1, front_back_dir1);
  digitalWrite(FRONT_BACK_DIR2, front_back_dir2);
  analogWrite(LEFT_RIGHT_ENABLE, stop);
  analogWrite(FRONT_BACK_ENABLE, stop);
}