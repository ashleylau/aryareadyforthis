#include <Arduino.h>
#include <IntervalTimer.h>
#include <Motors.h>
#include <Launcher.h>

void checkOff(void);

//Global variables
#define LIMIT_FRONT         14
#define LIMIT_BACK          15
#define LIMIT_SIDE          13

int turnTime = 500000;        //calibrate this based on how long to turn 90deg
int reloadTime = 7000000;   //pauses for 7s to reload the balls
int shootTime = 1000000;    //waits a second between shooting each ball
int ballCounter = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while(!Serial);

  pinMode(LIMIT_FRONT, INPUT_PULLUP);
  pinMode(LIMIT_BACK, INPUT_PULLUP);
  pinMode(LIMIT_SIDE, INPUT_PULLUP);

  //Start of the check-off process
  checkOff();

  //Eventually start the good code after check-off
}

void loop() {
  // put your main code here, to run repeatedly:
  //With check-off hard coding nothing should be on loop
}

void checkOff() {
  //Moves the robot to the back of the arena and then turns right
  motors.moveForward();
  while(!digitalRead(LIMIT_FRONT)){
    //wait
  }
  motors.turnRight();
  delay(turnTime);  
  //Moves the robot across the arena to the armoury, pausing when it hits the switch for 7 seconds
  motors.moveForward();
  while(!digitalRead(LIMIT_FRONT)){
    //wait
  }
  motors.stopMotors();
  delay(reloadTime); 
  //Turns the robot to move away from the switch to leave the armoury
  motors.turnRight();
  delay(turnTime);
  //Move to the front wall and start shooting at Casterly Rock
  motors.moveForward();
  while(digitalRead(LIMIT_FRONT)){
    //wait
  }
  motors.stopMotors();
  //Starts launching the balls at Casterly Rock
  launcher.startFlywheel();
  while (ballCounter < 6){
    launcher.incrementBall();
    delay(shootTime);
    ballCounter++;
  }
  launcher.stopFlywheel();
  launcher.returnRotator();
}