#include "Motors.h"
#include <Arduino.h>

/*----------Global Variables----------*/
int left_dir1 = LOW;
int left_dir2 = HIGH;
int right_dir1 = HIGH;
int right_dir2 = LOW;
int speed = 255;
int stop = 0;

MotorsClass motors;

/*----------Public Functions---------*/

MotorsClass::MotorsClass()
{
    begin();
}
/******************************************************************************
Function:     moveForward
Contents:     This function is used to set both the left and right motor to spin
              in the forward direction, moving the robot forward in a straight line.
Parameters:   None; if later set to move at different speeds this can be included.
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::moveForward(){
    left_dir1 = LOW;
    left_dir2 = HIGH;
    right_dir1 = HIGH;
    right_dir2 = LOW;
    digitalWrite(LEFT_MOTOR_DIR1, left_dir1);
    digitalWrite(LEFT_MOTOR_DIR2, left_dir2);
    digitalWrite(RIGHT_MOTOR_DIR1, right_dir1);
    digitalWrite(RIGHT_MOTOR_DIR2, right_dir2);
}

/******************************************************************************
Function:     moveBackward
Contents:     This function is used to set both the left and right motor to spin
              in the backward direction, moving the robot backwareds in a straight line.
Parameters:   None; if later set to move at different speeds this can be included.
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::moveBackward(){
    left_dir1 = HIGH;
    left_dir2 = LOW;
    right_dir1 = LOW;
    right_dir2 = HIGH;
    digitalWrite(LEFT_MOTOR_DIR1, left_dir1);
    digitalWrite(LEFT_MOTOR_DIR2, left_dir2);
    digitalWrite(RIGHT_MOTOR_DIR1, right_dir1);
    digitalWrite(RIGHT_MOTOR_DIR2, right_dir2);
}

/******************************************************************************
Function:     turnLeft
Contents:     This function is used to set the left motor to spin backward and the
              right motor to spin forward, moving the robot in a circle to the left.
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::turnLeft(){
    left_dir1 = HIGH;
    left_dir2 = LOW;
    right_dir1 = HIGH;
    right_dir2 = LOW;
    digitalWrite(LEFT_MOTOR_DIR1, left_dir1);
    digitalWrite(LEFT_MOTOR_DIR2, left_dir2);
    digitalWrite(RIGHT_MOTOR_DIR1, right_dir1);
    digitalWrite(RIGHT_MOTOR_DIR2, right_dir2);
}

/******************************************************************************
Function:     turnRight
Contents:     This function is used to set the left motor to spin forward and the
              right motor to spin backward, moving the robot in a circle to the right.
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::turnRight(){
    left_dir1 = LOW;
    left_dir2 = HIGH;
    right_dir1 = LOW;
    right_dir2 = HIGH;
    digitalWrite(LEFT_MOTOR_DIR1, left_dir1);
    digitalWrite(LEFT_MOTOR_DIR2, left_dir2);
    digitalWrite(RIGHT_MOTOR_DIR1, right_dir1);
    digitalWrite(RIGHT_MOTOR_DIR2, right_dir2);
}

/******************************************************************************
Function:     stopMotors
Contents:     This function is used to turn both motors off, stopping the robot.
Parameters:   None
Returns:      Nothing; function is of type void
******************************************************************************/
void MotorsClass::stopMotors(){
    analogWrite(LEFT_MOTOR_ENABLE, stop);
    analogWrite(RIGHT_MOTOR_ENABLE, stop);
}

/*----------Private Functions---------*/
//Private function to initialize pins when the motor class is first included
void MotorsClass::begin( ) { 
  Serial.begin(9600);

  //  Set up the pin modes
  pinMode(LEFT_MOTOR_ENABLE, OUTPUT);
  pinMode(LEFT_MOTOR_DIR1, OUTPUT);
  pinMode(LEFT_MOTOR_DIR2, OUTPUT);
  pinMode(RIGHT_MOTOR_ENABLE, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR1, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR2, OUTPUT);

  //  Set the speeds and directions to initial values
  digitalWrite(LEFT_MOTOR_DIR1, left_dir1);
  digitalWrite(LEFT_MOTOR_DIR2, left_dir2);
  digitalWrite(RIGHT_MOTOR_DIR1, right_dir1);
  digitalWrite(RIGHT_MOTOR_DIR2, right_dir2);
  analogWrite(LEFT_MOTOR_ENABLE, speed);
  analogWrite(RIGHT_MOTOR_ENABLE, speed);
}
